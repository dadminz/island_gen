

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


//comparators for sorting the class in a list structure etc:
bool point2D::compare_x (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second)
{  
  return ( (first->x) < (second->x) );
}
bool point2D::compare_y (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second)
{  
  return ( (first->y) < (second->y) );
}
bool point2D::compare_pointID (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second)
{  
  return ( (first->pointID) < (second->pointID) );
}

//######################################################################
//Constructor of Edge

//######################################################################
//Constructor of Triangle

//######################################################################
//Constructor of ConvexHull






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
		//cv::putText(mat, std::to_string((*it)->pointID) , (*it)->cvp2f(), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255,255,255), 1);
	}	
}

void pointField::plotPList()
{
	for (std::list<std::shared_ptr<point2D>>::iterator it = PList.begin(); it != PList.end(); ++it)
	{
		std::cout << "ID: " << (*it)->pointID <<" Point: " << (*it)->cvp2f() << std::endl;
	}	
}

bool pointField::compare_R2 (const std::shared_ptr<point2D> &first, const std::shared_ptr<point2D> &second, const std::shared_ptr<point2D> &Pseed)
{  
	if ( ( pow(((first->x)-(Pseed->x)),2) +pow(((first->y) - (Pseed->y)),2) <  pow(((second->x)-(Pseed->x)),2) +pow(((second->y) - (Pseed->y)),2)) )
	{
		return true;
	}
	return false;	
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

void pointField::sortPoints()
{
	std::cout << "===================================" << std::endl;
	std::cout << "calling sortPoints():" << std::endl;
	
	std::cout << std::endl;	
	std::cout << "Unsorted List:" << std::endl;		
	plotPList();
	
	std::cout << std::endl;	
	std::cout << "sorted List by x: " << std::endl;		
	PList.sort(point2D::compare_x);
	plotPList();
	
	std::cout << std::endl;	
	std::cout << "sorted List by y:" << std::endl;		
	PList.sort(point2D::compare_y);
	plotPList();
	
	Pseed = PList.front();
	std::cout << "Pseed: " << Pseed->cvp2f() << std::endl;	
	
	std::cout << std::endl;	
	std::cout << "sorted List by R2:" << std::endl;		
	//PList.sort(compare_R2(Pseed));
	
	
	plotPList();
	
		
}


