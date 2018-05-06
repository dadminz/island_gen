/*
void testbench(cv::Mat &mat)
{
	std::cout << "Calling: " << "testbench()" << std::endl;		
	
	pointField field;	
	field.genPoints(0,mat.cols,0,mat.rows,10);
	field.plotField(mat);
	field.sortPoints();
	

}
*/

void testbench(cv::Mat &mat)
{
	std::cout << "Calling: " << "testbench()" << std::endl;		
	
	//Generate 3 new points via shared_ptr handles
	std::shared_ptr<geo_point2D> p1 = std::make_shared<geo_point2D>(100,100,1); 
	std::shared_ptr<geo_point2D> p2 = std::make_shared<geo_point2D>(200,150,2); 
	std::shared_ptr<geo_point2D> p3 = std::make_shared<geo_point2D>(150,200,3);
	
	//Generate Triangle with Points
	std::shared_ptr<geo_triangle2D> tri = std::make_shared<geo_triangle2D>(p1,p2,p3);
	//Associate the Points with the Triangle (for two way association)
	p3->ConTriangles.push_back(tri);
	p2->ConTriangles.push_back(tri);
	p1->ConTriangles.push_back(tri);
	
	tri->plot_me(mat);
	
	std::cout << "tri Point id's:[" << tri->Ptri[0]->id << " , " << tri->Ptri[1]->id << " , " << tri->Ptri[2]->id << "] " << std::endl;
	
	std::cout << "tri use count: " << tri.use_count() << std::endl;
}




