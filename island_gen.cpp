#include "source/include.h"


void my_programm()
{
	//Initializing the Canvas CV_8UC3 8bits unsigned with 3 color channels Blue Green Red (BGR)
	cv::Mat canvas = cv::Mat::zeros(cv::Size(1300, 800), CV_8UC3);		
		
	//Initializing Mask (Layer)
	cv::Mat  layer = cv::Mat( canvas.size() , canvas.type() , cv::Scalar(0,0,0) );
	cv::Mat output = cv::Mat( canvas.size() , canvas.type() , cv::Scalar(0,0,0) );		
	//canvas.setTo( cv::Scalar(0,0,0) );
	//layer.setTo( cv::Scalar(0,0,0) );
	//output.setTo( cv::Scalar(0,0,0) );
	cv::namedWindow("Display Output", cv::WINDOW_AUTOSIZE );
		
	int grid_div_x = 10;
	int grid_div_y = 10;
	int grid_div_major= 100;
	plot_line_grid(canvas,grid_div_x,grid_div_y,grid_div_major,cv::Scalar(30,30,30),1);
	
	std::string text = "Island Gen V0.01";    
    cv::putText(canvas, text , cv::Point2f(5,15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(90,255,90), 1);	
	std::cout << "Starting: " << text << std::endl;
	//----------------------------------------------------------------
	
	
	
	testbench(layer);

	
	//----------------------------------------------------------------
	cv::imshow("Display Output", canvas+layer);       
    cv::waitKey(0);
}

int main()
{
	my_programm();
	return 0;
}
