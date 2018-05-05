
void randPoint2f(cv::Point2f &point, std::default_random_engine &generator)
{
  //std::cout << "Calling: " << "randPoint2f()" << std::endl;
  //std::default_random_engine generator;
  
  //std::uniform_real_distribution<double> distribution(0.0,1.0);
  
  std::normal_distribution<float> distribution(0.5,0.1);
  
  point.x = distribution(generator);
  point.y = distribution(generator);  
  
  //std::cout << "Random Point: " << point << std::endl; 
  	
}




void testbench(cv::Mat &mat)
{
	std::cout << "Calling: " << "testbench()" << std::endl;
	
	//cv::line(mat,cv::Point2f(100,100),cv::Point2f(200,200),cv::Scalar(150,150,150),2,1);
	
	cv::Point2f nrP;		//Normalized Random Point
	cv::Point2f Point;		//Point on Canvas
	
	std::default_random_engine RandGenerator;
	
	for(int i=1; i<= 10000; i++)
	{
		randPoint2f(nrP,RandGenerator);
		Point.x = nrP.x * mat.cols;
		Point.y = nrP.y * mat.rows;		
		cv::circle(mat, Point, 1, cv::Scalar(255,255*nrP.x,255*nrP.y), CV_FILLED, CV_FILLED );
		//cv::imshow("Display Output", mat);       
		//cv::waitKey(1);	
	}
	
	
}
