//######################################################################
//2D Point
geo_point2D::geo_point2D(float tx, float ty,int tid)
{
	std::cout << "calling constructor geo_point2D(ID:"<< tid << " x:" << tx << " iy:" << ty << ")" << std::endl;
	x = tx;
	y = ty;
	id = tid;
}
//######################################################################
//2D Edge
geo_edge2D::geo_edge2D(std::shared_ptr<geo_point2D> A, std::shared_ptr<geo_point2D> B, int tid)
{std::cout << "calling constructor geo_edge2D(id: "<< tid << " pid1: " << A->id<< " pid2: "<< B->id << ")" << std::endl;
	
	id = tid;
	Pedge.push_back(A);
	Pedge.push_back(B);
}

//######################################################################
//2D Triangle
geo_triangle2D::geo_triangle2D(std::shared_ptr<geo_edge2D> a, std::shared_ptr<geo_edge2D> b, std::shared_ptr<geo_edge2D> c, int tid)	
{
	std::cout << "calling constructor geo_triangle2D()" << std::endl;
	id = tid;
	
	
	Etri.push_back(a);
	Etri.push_back(b);
	Etri.push_back(c);
	
	Ptri.push_back(a->Pedge[0]);
	Ptri.push_back(b->Pedge[0]);
	Ptri.push_back(c->Pedge[0]);	
}

void geo_triangle2D::plot_me(cv::Mat &mat)
{	
	cv::line(mat, cv::Point2f(Ptri[0]->x,Ptri[0]->y) , cv::Point2f(Ptri[1]->x,Ptri[1]->y),cv::Scalar(150,150,150),1,1); 
	cv::line(mat, cv::Point2f(Ptri[1]->x,Ptri[1]->y) , cv::Point2f(Ptri[2]->x,Ptri[2]->y),cv::Scalar(150,150,150),1,1); 
	cv::line(mat, cv::Point2f(Ptri[2]->x,Ptri[2]->y) , cv::Point2f(Ptri[0]->x,Ptri[0]->y),cv::Scalar(150,150,150),1,1); 
}
//######################################################################
//2D Mesh
geo_mesh2D::geo_mesh2D(int tid)
{
	std::cout << "calling constructor geo_mesh2D()" << std::endl;
	id = tid;
}
