//classes for Geometry stuff:

//######################################################################
//Prototypes:
class geo_point2D;
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
		
		float x;	//x-Coord of the Point
		float y;	//y-Coord of the Point
		int id;
		std::vector<std::shared_ptr<geo_triangle2D>> ConTriangles = {};	
};

//######################################################################
//2D Triangle

class geo_triangle2D
{	//Class for storing a 2D Triangle and associated Data
	private:
		
	public:
		geo_triangle2D(std::shared_ptr<geo_point2D> A, std::shared_ptr<geo_point2D> B, std::shared_ptr<geo_point2D> C); // Constructor
		void plot_me(cv::Mat &mat);
		
		float MP;	// Meridian Point of the Triangle
		
		std::vector<std::shared_ptr<geo_point2D>> Ptri = {};	//3 Points defining the Triangle
	
};
//######################################################################
//2D Mesh

class geo_mesh2D
{	//Class for storing a 2D Mesh and associated Data
	private:
	
	public:
		geo_mesh2D(); // Constructor
		void plot_me(cv::Mat &mat);
	
};
