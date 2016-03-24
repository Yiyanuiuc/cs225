/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:

    /*
     * default constructor 
     * The first takes no arguments, and produces an empty Quadtree object, 
     * i.e., one which has no associated QuadtreeNode objects, and in which root is NULL. 
     */
    Quadtree ();

    /* 
     * This constructor's purpose is to build a Quadtree representing the upper-left d by d block of the source image.
     * This effectively crops the source image into a d by d square.
     * You may assume that d is a power of two, and that the width and height of source are each at least d.
     * Perhaps, to implement this, you could leverage the functionality of another function you have written in 5.1...
     * @param source The source image to base this Quadtree on
     * @param solution The width and height of the sides of the image to be represented
     */
    Quadtree (PNG const & source, int resolution); 

    /*
     * Copy constructor.
     * Simply sets this Quadtree to be a copy of the parameter.
     * @param other The Quadtree to make a copy of
     */
    Quadtree (const Quadtree & other);

    /* destructor */
    ~Quadtree (); 

    /* 
     * Assignment operator
     * Frees memory associated with this Quadtree and sets its contents to be equal to the parameter's.
     * @param other The Quadtree to make a copy of
     * @return A constant reference to the Quadtree value that was copied
     */
    const Quadtree & operator = (const Quadtree & other);

    /*
     * Deletes the current contents of this Quadtree object, then turns it into a Quadtree object representing the upper-left d by d block of source.
     * You may assume that d is a power of two, and that the width and height of source are each at least d.
     * @param source The source image to base this Quadtree on
     * @param resolution The width and height of the sides of the image to be represented
     */
    void buildTree (PNG const & source, int resolution);

    /*
     * Gets the RGBAPixel corresponding to the pixel at coordinates (x, y) in the bitmap image which the Quadtree represents.
     * Note that the Quadtree may not contain a node specifically corresponding to this pixel (due, for instance, to pruning - see below). 
     * In this case, getPixel will retrieve the pixel (i.e. the color) of the square region within which the smaller query grid cell would lie. 
     * (That is, it will return the element of the nonexistent leaf's deepest surviving ancestor.) 
     * If the supplied coordinates fall outside of the bounds of the underlying bitmap, or if the current Quadtree is "empty" 
     * (i.e., it was created by the default constructor) 
     * then the returned RGBAPixel should be the one which is created by the default RGBAPixel constructor.
     * @param x The x coordinate of the pixel to be retrieved
     * @param y The y coordinate of the pixel to be retrieved
     * @return The pixel at the given (x, y) location
     */
    RGBAPixel getPixel (int x, int y) const;

    /*
     * Returns the underlying PNG object represented by the Quadtree.
     * If the current Quadtree is "empty" (i.e., it was created by the default constructor) 
     * then the returned PNG should be the one which is created by the default PNG constructor. 
     * @return The decompressed PNG image this Quadtree represents
     */
    PNG decompress() const; 

    /**
     * Rotates the Quadtree object's underlying image clockwise by 90 degrees.
     */
    void clockwiseRotate ();

    /**
     * Compresses the image this Quadtree represents.
     * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
     */
    void prune (int tolerance);   

    /**
     * This function is similar to prune; however, it does not actually prune the Quadtree.
     * Rather, it returns a count of the total number of leaves the Quadtree would have if it were pruned as in the prune function.
     * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
     * @return How many leaves this Quadtree would have if it were pruned with the given tolerance.
     */
    int pruneSize (int tolerance) const;

    /**
     * Calculates and returns the minimum tolerance necessary to guarantee that upon pruning the tree, no more than numLeaves leaves remain in the Quadtree.
     * @param numLeaves The number of leaves you want to remain in the tree after prune is called.
     * @returns The minimum tolerance needed to guarantee that there are no more than numLeaves remaining in the tree.
     */
    int idealPrune (int numLeaves) const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
    public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */

        /*
         * default constructor for QuadtreeNode
         */
        QuadtreeNode() ;
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    /* 
     * Your Quadtree objects will probably need some way of 
     * remembering the resolution of their underlying bitmaps.
     */
    int resolution; 

    /*
     * a helper function for copy
     * assume the input subRoot!=NULL;
     * @param subRoot 
     * @param sourceRoot the QuadtreeNOde * to make a copy of
     */
    void copy (QuadtreeNode * & subRoot, QuadtreeNode * sourceRoot);

    /*
     * clear helper function
     * @param subRoot
     */
    void clear(QuadtreeNode * & subRoot);

    /*
     * a helper function for buildTree
     * @param source The source image to base this Quadtree on
     * @param subRoot
     * @param xCoord
     * @param yCoord
     * @param resolution The remaining size
     */
    void assignPixel (PNG const & source, QuadtreeNode * & subRoot, int xCoord, int yCoord, int resolution);

    /* 
     * a helper function to get the pixel 
     * @param subRoot
     * @param xCoord
     * @param yCoord
     * @param resolution The remaining size
     */
    RGBAPixel getPixel (QuadtreeNode * subRoot, int xCoord, int yCoord, int resolution) const; 

    /* 
     * a helper function to get the pixel
     * @param img The reference of image to paint
     * @param subRoot
     * @param xCoord
     * @param yCoord
     * @param resolution The remaining size
     */
    void decompress(PNG & img, QuadtreeNode * subRoot, int xCoord, int yCoord, int resolution) const;

    /**
     * helper function for clockwiseRotate
     * @param subRoot
     */
    void clockwiseRotate (QuadtreeNode * subRoot);

    /**
     * helper function for prune
     * @param subRoot
     * @param temp
     * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
     * @return bool whether the node should be pruned
     */
    bool toBePruned (QuadtreeNode * & subRoot, QuadtreeNode * & temp, int tolerance) const;

    /**
     * helper function for prune
     * @param subRoot
     * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
     */
    void prune (QuadtreeNode * & subRoot, int tolerance);

    /**
     * helper function for pruneSIze
     * @param subRoot
     * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
     * @return How many leaves this Quadtree would have if it were pruned with the given tolerance below the subRoot.
     */
    int pruneSize (QuadtreeNode * subRoot, int tolerance) const;

    /**
     * helper function for idealPrune
     * @param start
     * @param end 
     * @param numLeaves The number of leaves you want to remain in the tree after prune is called.
     * @returns The minimum tolerance needed to guarantee that there are no more than numLeaves remaining in the tree.
     */
    int idealPrune (int startP, int endP, int numLeaves) const;

/**** Functions for testing/grading ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
