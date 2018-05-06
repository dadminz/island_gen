//-----------------------------------------------------
// Classes for storing complex point information
// 
//-----------------------------------------------------

//######################################################################
//Class for Storing 2D Point information with relationship to other points
class point2D
{
	
	private:
		
	public:		
		point2D(float xin, float yin, int ID);	//Constructor
		cv::Point2f cvp2f();	//returns x and y coords as a cv::point2f
		
		
		static bool compare_x (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second);
		static bool compare_y (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second);
		static bool compare_pointID (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second);		
		int pointID;
		float x;
		float y;
		
		std::list<std::shared_ptr<point2D>> connections = {};
};
//std::shared_ptr<float> pvar = std::make_shared<float>(1.1);

//######################################################################
//Class for Edge
class Edge
{
	private:
	
	public:
	
	//2 Points
};

//######################################################################
//Class for Triangle
class Triangle
{
	private:
	
	public:
	
	//3 Points
	//3 Edges
};

//######################################################################
//Class for generating a Point field and processing the Points further.
class pointField
{
	private:
		
		std::default_random_engine RandGenerator;
	
	public:
		pointField();	//Constructor
		void plotField(cv::Mat &mat);	//Function for plotting the point of the field	
		void plotPList();	//Function for plotting the list of points to the console
		static bool compare_R2 (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second, const std::shared_ptr<point2D> &Pseed);
			
		void genPoints(float xmin, float xmax, float ymin, float ymax,int N);	//Function for Generating N Points in limited Area
		void sortPoints();	//Function for sorting the Points in the PList
		
		std::shared_ptr<point2D> Pseed;
		
		std::list<std::shared_ptr<point2D>> PList = {};
	
};
