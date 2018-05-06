

//######################################################################
//Constructor of point2D
point2D::point2D(float xin, float yin, int ID)
{
	std::cout << "calling constructor point2D(x:"<< xin <<" y:"<< yin <<" ID:" <<ID<< ")"<< std::endl;	
	x = xin;
	y = yin;
	pointID=ID;
}

cv::Point2f point2D::cvp2f()
{
	//returns the Point coords as a cv::Point2f object
	return cv::Point2f(x,y);
}

//######################################################################
//Constructor of pointField

pointField::pointField()
{
	std::cout << "calling constructor pointField()" << std::endl;
}

void pointField::plotField(cv::Mat &mat)
{	
	std::cout << "calling plotField()" << std::endl;
	
	for (std::list<std::shared_ptr<point2D>>::iterator it = PList.begin(); it != PList.end(); ++it)
	{
		
		cv::circle(mat, (*it)->cvp2f(), 3, cv::Scalar(0,0,255), CV_FILLED, CV_FILLED );
		cv::putText(mat, std::to_string((*it)->pointID) , (*it)->cvp2f(), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255,255,255), 1);
	}	
}

void pointField::genPoints(float xmin, float xmax, float ymin, float ymax,int N)
{
	std::cout << "calling genPoints():" << std::endl;
	std::cout << "xmin:" << xmin << " xmax:" << xmax << " ymin:" << ymin << " ymax:" << ymax << " N:" << N <<std::endl;
	
	int ID = 0;
	float rand_x = 0.0;
	float rand_y = 0.0;
	
	std::uniform_real_distribution<float> distribution_x(xmin,xmax);
	std::uniform_real_distribution<float> distribution_y(ymin,ymax);
	
	for(int i=1;i<=N;i++)
	{		
		ID=i;
		rand_x = distribution_x(RandGenerator);
		rand_y = distribution_y(RandGenerator);
		PList.push_back(std::make_shared<point2D>(rand_x,rand_y,ID));
	}
}
