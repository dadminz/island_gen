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
	
	geo_mesh2D mesh(1);
	
	mesh.test_generator(mat);
}




