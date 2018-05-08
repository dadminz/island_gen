//classes for Geometry stuff:

//######################################################################
//Prototypes:
class geo_point2D;
class geo_edge2D;
class geo_triangle2D;
class geo_mesh2D;

//######################################################################
//2D Point

class geo_point2D
{	//Class for storing a 2D Point and associated Data
	private:
	
	public:
		geo_point2D(float tx, float ty,int tid);	//Constructor
		void plot_me(cv::Mat &mat);
		cv::Point2f cvp2f();						//returns the Point coords as a cv::Point2f object
		
		int id;
		float x;	//x-Coord of the Point
		float y;	//y-Coord of the Point
		
		std::vector<std::shared_ptr<geo_edge2D>> ConEdges = {};	
		std::vector<std::shared_ptr<geo_triangle2D>> ConTriangles = {};	
};
//######################################################################
//2D Edge
class geo_edge2D
{	//Class for storing a 2D Edge and associated Data
	private:
	
	public:
		geo_edge2D(std::shared_ptr<geo_point2D> A, std::shared_ptr<geo_point2D> B, int tid); //Constructor
		
		int id;
		
		std::vector<std::shared_ptr<geo_point2D>> Pedge = {};	//2 Points defining the Edge
		std::shared_ptr<geo_edge2D> CommonEdge;					//Edge sharing the same Points as this edge if available
		std::shared_ptr<geo_triangle2D> ConTriangle;			//Triangle this edge is part of
};

//######################################################################
//2D Triangle

class geo_triangle2D
{	//Class for storing a 2D Triangle and associated Data
	private:
		
	public:
		geo_triangle2D(std::shared_ptr<geo_edge2D> a, std::shared_ptr<geo_edge2D> b, std::shared_ptr<geo_edge2D> c, int tid); // Constructor
		void plot_me(cv::Mat &mat);
		
		int id;
		float MP;	// Meridian Point of the Triangle
		
		std::vector<std::shared_ptr<geo_point2D>> Ptri = {};	//3 Points defining the Triangle
		std::vector<std::shared_ptr<geo_edge2D>> Etri = {};		//3 Edges defining the Triangle
};
//######################################################################
//2D Mesh

class geo_mesh2D
{	//Class for storing a 2D Mesh and associated Data
	private:
		std::default_random_engine RandGenerator;		
		int id_point_count;
		int id_edge_count;
		int id_triangle_count;		
	public:
		geo_mesh2D(int tid); // Constructor
		int id_gen_point(); int id_gen_edge(); int id_gen_triangle();
		void plot_me(cv::Mat &mat);		
		
		//generates a triangle from 3 points and makes all the associations happen
		void triangle_generator(std::shared_ptr<geo_point2D> p1,std::shared_ptr<geo_point2D> p2,std::shared_ptr<geo_point2D> p3);
		
		//function for generating an grid of points
		void point_grid_generator(int count_x, int count_y, float dx, float dy);		
		
		//function for triangulating an grid of points
		void point_grid_triangulator(int count_x, int count_y);
		
		//function for deforming an grid of points
		void point_grid_DeformerRand(int count_x, int count_y, float dx ,float dy);
		
		void summary();		//function for ploting the number of stuff in the mesh
		void test_generator(cv::Mat &mat);		//test function		
		
		int id;		
		std::vector<std::shared_ptr<geo_point2D>> M_points = {};			//List for Storing all Points of the mesh
		std::vector<std::shared_ptr<geo_edge2D>> M_edges = {};			//List for Storing all Edges of the mesh
		std::vector<std::shared_ptr<geo_triangle2D>> M_triangles = {};	//List for Storing all Triangles of the Mesh
	
};







