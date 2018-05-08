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
	int count_x = 12;
	int count_y = 7;
	
	//mesh.test_generator(mat);
	mesh.summary();
	mesh.point_grid_generator(count_x,count_y,100,100);	
	mesh.point_grid_triangulator(count_x,count_y);	
	
	mesh.point_grid_DeformerRand(count_x,count_y,15,15);
	
	//mesh.M_points[42]->x = mesh.M_points[42]->x + 50;
	//mesh.M_points[42]->y = mesh.M_points[42]->y + 30;
	
	mesh.summary();

	mesh.plot_me(mat);
}




