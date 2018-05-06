
void randPoint2f(cv::Point2f &point, std::default_random_engine &generator)
{
  //std::cout << "Calling: " << "randPoint2f()" << std::endl;
  //std::default_random_engine generator;
  
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  
  //std::normal_distribution<float> distribution(0.5,0.1);
  
  point.x = distribution(generator);
  point.y = distribution(generator);  
  
  //std::cout << "Random Point: " << point << std::endl; 
  
  //for use:
  //std::default_random_engine RandGenerator;
  //cv::Point2f nrP;
  //randPoint2f(nrP,RandGenerator);
  
  //cv::line(mat,cv::Point2f(100,100),cv::Point2f(200,200),cv::Scalar(150,150,150),2,1); 	
}




void testbench(cv::Mat &mat)
{
	std::cout << "Calling: " << "testbench()" << std::endl;		
	
	pointField field;
	
	field.genPoints(0,mat.cols,0,mat.rows,10);
	field.plotField(mat);
	field.sortPoints();		
}







