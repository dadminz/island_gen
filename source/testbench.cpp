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
	
	//Generate 3 new edges with the defined points:	
	std::shared_ptr<geo_edge2D> e1 = std::make_shared<geo_edge2D>(p1,p2,1);
	std::shared_ptr<geo_edge2D> e2 = std::make_shared<geo_edge2D>(p2,p3,2);
	std::shared_ptr<geo_edge2D> e3 = std::make_shared<geo_edge2D>(p3,p1,3);
	
	//Associate the Points with the Edges (for two way association)
	p1->ConEdges.push_back(e1);		p1->ConEdges.push_back(e3);	
	p2->ConEdges.push_back(e1);		p2->ConEdges.push_back(e2);	
	p3->ConEdges.push_back(e2);		p3->ConEdges.push_back(e3);	
	
	//Generate Triangle with Edges:
	std::shared_ptr<geo_triangle2D> tri = std::make_shared<geo_triangle2D>(e1,e2,e3,1);	
	
	//Associate the Points with the Triangle (for two way association)
	p1->ConTriangles.push_back(tri);	p2->ConTriangles.push_back(tri);	p3->ConTriangles.push_back(tri);
	
	//associate the Edges with the Triangle (for two way association)	
	e1->ConTriangle = tri;	e2->ConTriangle = tri;	e3->ConTriangle = tri;

	
	
	
	
	tri->plot_me(mat);
	
	std::cout << "tri Point      id's:[" << tri->Ptri[0]->id << " , " << tri->Ptri[1]->id << " , " << tri->Ptri[2]->id << "] " << std::endl;
	std::cout << "tri Edge       id's:[" << tri->Etri[0]->id << " , " << tri->Etri[1]->id << " , " << tri->Etri[2]->id << "] " << std::endl;
	std::cout << "tri Edge 1st P id's:[" << tri->Etri[0]->Pedge[0]->id << " , " << tri->Etri[1]->Pedge[0]->id << " , " << tri->Etri[2]->Pedge[0]->id << "] " << std::endl;
	std::cout << "tri Edge 2nd P id's:[" << tri->Etri[0]->Pedge[1]->id << " , " << tri->Etri[1]->Pedge[1]->id << " , " << tri->Etri[2]->Pedge[1]->id << "] " << std::endl;
		
}




