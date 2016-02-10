#include "octree.h"


namespace myOctree {


//Member functions
bool Octree::isLeafNode() {
    
    return children[0][0][0] == NULL;
}

bool Octree::isRootNode() {
    
    return parent == NULL;
}

Block* Octree::get_block_data() {
    
    return block_data;
}

void Octree::coarsen() {
    
    
    if(this->isLeafNode()&&!(this->isRootNode()))  {
        
        //delete this;
        nodes.remove(this);
        
    }
    //        moving to its parent
    //        this->current = this->parent;
    //
    //        deleting all children
    //        for(int i=0; i<2; i++) {
    //                for(int j=0; j<2; j++) {
    //                        for(int k=0; k<2; k++)
    //                                this->current->children[i][j][k] = NULL;
    //                }
    //        }
    //
    //        delete this;
    
}

void Octree::refine() {
    
    int i, j, k;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    double lev = this->level + 1;
    
    //creating children nodes
    for(k=0; k<2; k++) {
        for(j=0; j<2; j++) {
            for(i=0; i<2; i++) {
                
                if(i==0) {
                    xmin = this->x_min;
                    xmax = this->x_centre;
                }
                else {
                    xmin = this->x_centre;
                    xmax = this->x_max;
                }
                
                if(j==0) {
                    ymin = this->y_min;
                    ymax = this->y_centre;
                }
                else {
                    ymin = this->y_centre;
                    ymax = this->y_max;
                }
                
                if(k==0) {
                    zmin = this->z_min;
                    zmax = this->z_centre;
                }
                else {
                    zmin = this->z_centre;
                    zmax = this->z_max;
                }
                
                //creating new memory locations to children
                children[i][j][k] = new Octree;
                
                //creating new child object
                Octree child(xmin, xmax, ymin, ymax, zmin, zmax, lev);
                
                //deleting the pushed node to the list
                nodes.pop_back();
                
                //assigning parent to the child
                child.parent = this;
                
                //invoking copy constructor
                *(this->children[i][j][k]) = child;
            }
        }
    }
    
    //	//assigning each child its siblings
    //	int local_sibling_count;
    //	for(i=0; i<8; i++) {
    //		local_sibling_count = 0;
    //		for(j=0; j<8; j++) {
    //			if(i==j) continue;
    //			node[i].siblings[local_sibling_count] = &node[j];
    //			local_sibling_count++;
    //		}
    //	}
    //
    //
}

Octree::~Octree() {
    
    //	for(int i=0; i<2; i++) {
    //                for(int j=0; j<2; j++) {
    //                        for(int k=0; k<2; k++)
    //                                delete children[i][j][k];
    //                }
    //        }
    //
    //
    //
    //        delete [] children;
    //
    //        delete block_data;
    //
    //        delete parent;
    //
    //        delete current;
    //
    //        delete [] siblings;
}

Octree::Octree(const Octree &obj) {
    
    
    x_min = obj.x_min;
    y_min = obj.y_min;
    z_min = obj.z_min;
    x_max = obj.x_max;
    y_max = obj.y_max;
    z_max = obj.z_max;
    x_centre = obj.x_centre;
    y_centre = obj.y_centre;
    z_centre = obj.z_centre;
    level = obj.level;
    parent = obj.parent;
    block_data = obj.block_data;
    
    memcpy(children,obj.children,sizeof(Octree***)*2);
    for(int i=0;i<2;i++) {
        memcpy(children[i],obj.children[i],sizeof(Octree**)*2);
        for(int j=0;j<2;j++) {
            memcpy(children[i][j],obj.children[i][j],sizeof(Octree*)*2);
        }
    }
}

Octree::Octree( double x1, double x2, double y1, double y2, double z1, double z2, int l ) : x_min(x1), x_max(x2), y_min(y1), y_max(y2), z_min(z1), z_max(z2), level(l)   {
    
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            for(int k=0; k<2; k++)
                children[i][j][k] = NULL;
        }
    }
    
    if(level==0)
        parent = NULL;
    
    
    x_centre = (x_min + x_max ) / 2.0;
    y_centre = (y_min + y_max ) / 2.0;
    z_centre = (z_min + z_max ) / 2.0;
    
    
    //creating block to assign it to the data
    block_data = new Block;
    Block new_block(x_min, x_max, y_min, y_max, z_min, z_max);
    *block_data = new_block;
    
    //printf("dx=%g, dy=%g, dz=%g \n", block_data->dx, block_data->dy, block_data->dz);
    
    //make current pointer point to the current object
    //      current = this;
    
    nodes.push_back(this);
    
}

Octree::Octree() {
    
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            for(int k=0; k<2; k++)
                children[i][j][k] = NULL;
        }
    }
    
    if(level==0)
        parent = NULL;
    
    //creating block to assign it to the data
    block_data = new Block;
    Block new_block;
    *block_data = new_block;
    
    //make current pointer point to the current object
    //      current = this;
    nodes.push_back(this);
}


}
