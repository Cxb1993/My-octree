#ifndef MYOCTREE_OCTREE_H_
#define MYOCTREE_OCTREE_H_
#include <stdio.h>
#include <list>
#include "block.h"

namespace myOctree {


//class forward declaration
class Octree;
extern std::list<Octree*> nodes;


//OCTREE CLASS
//This class is used to create octree datastructure which stores in each of its nodes, a block of grid data in the block-based AMR mesh.
//Objects of this class are nodes of the tree.
//When a new object is created, children are assigned, parent is assigned, data block is assigned and finally the pointer of the object is pushed into the "nodes" list.  
//
//Usage:
//Octree object(x min, x max, y min, y max, z min, z max, level); 
//This creates a node of the tree at the specified level.
//This object can be further refined or coarsened using member functions of this class.
class Octree {

	public:
	//default constructor
	Octree();
	
	//parametrized constructor with initialization fields
	Octree( double x1, double x2, double y1, double y2, double z1, double z2, int l );

	//Copy constructor
        Octree(const Octree &obj);

	//destructor
	~Octree();

	//adds 8 children 
	void refine();

	//removes the object 
	void coarsen(); 

	//function to test if leaf node
	bool isLeafNode();

	//function to test if root node
	bool isRootNode();

	//function to test if the point lies inside the block
	bool contains(double x, double y, double z);

	//gets level of the node
	int get_level();	
		
	//function to access block_data
	Block* get_block_data();

	//variable to know whether to refine the node or not
	bool setToRefine;

	//variable to know whether to coarsen the node or not
	bool setToCoarsen;
	
	private:
	//each node has upto 8 children (2^3 for 3 dimensions) 
	Octree *children[2][2][2];
	
	//each node stores a block of grid cells
	Block *block_data;

	//pointer to the parent
	Octree *parent;

	//pointer to the current node
//	Octree *current;

	//level in the tree
	int level;

	//siblings
	//Octree *siblings[7];

	//node's block dimensions
	double x_centre, y_centre, z_centre;
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;

	
	protected:	

};


//function declarations
//void write_vtk(std::list<Octree*>&);

}
#endif
