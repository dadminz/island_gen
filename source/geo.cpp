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
//2D Triangle
geo_triangle2D::geo_triangle2D(std::shared_ptr<geo_point2D> A, std::shared_ptr<geo_point2D> B, std::shared_ptr<geo_point2D> C)	
{
	std::cout << "calling constructor geo_triangle2D()" << std::endl;
	Ptri.push_back(A);
	Ptri.push_back(B);
	Ptri.push_back(C);	
}

void geo_triangle2D::plot_me(cv::Mat &mat)
{	
	cv::line(mat, cv::Point2f(Ptri[0]->x,Ptri[0]->y) , cv::Point2f(Ptri[1]->x,Ptri[1]->y),cv::Scalar(150,150,150),1,1); 
	cv::line(mat, cv::Point2f(Ptri[1]->x,Ptri[1]->y) , cv::Point2f(Ptri[2]->x,Ptri[2]->y),cv::Scalar(150,150,150),1,1); 
	cv::line(mat, cv::Point2f(Ptri[2]->x,Ptri[2]->y) , cv::Point2f(Ptri[0]->x,Ptri[0]->y),cv::Scalar(150,150,150),1,1); 
}
//######################################################################
//2D Mesh
geo_mesh2D::geo_mesh2D()
{
	std::cout << "calling constructor geo_mesh2D()" << std::endl;
}
