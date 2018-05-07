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
	std::cout << "calling constructor geo_triangle2D(id: " << tid << " e1-id: " << a->id << " e2-id: " << b->id << " e3-id: " << c->id <<" )" << std::endl;
	id = tid;
	
	//TODO: checking and enforcing ccw or cw orientation of the Edges!
	Etri.push_back(a);
	Etri.push_back(b);
	Etri.push_back(c);
	
	//TODO: checking and enforcing ccw or cw orientation of the Points!
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
	id_point_count = 0;
	id_edge_count = 0;
	id_triangle_count = 0;
}

int geo_mesh2D::id_gen_point() { id_point_count++; return id_point_count; }
int geo_mesh2D::id_gen_edge() { id_edge_count++; return id_edge_count; }
int geo_mesh2D::id_gen_triangle() { id_triangle_count++; return id_triangle_count; }

void geo_mesh2D::test_generator(cv::Mat &mat)
{
	std::cout << "calling geo_mesh2D.test_generator()" << std::endl;
	
	//------------------------------------------------------------------
	//Workflow for creating a Triangle:
	
	//OPTIONAL: Generate 3 new points via shared_ptr handles else use external points
	std::shared_ptr<geo_point2D> p1 = std::make_shared<geo_point2D>(100,100,id_gen_point()); 
	std::shared_ptr<geo_point2D> p2 = std::make_shared<geo_point2D>(200,150,id_gen_point()); 
	std::shared_ptr<geo_point2D> p3 = std::make_shared<geo_point2D>(150,200,id_gen_point());
	
	//Points p1,p2,p3 must be cw oriented, there is no checking of the orientation yet!
	//Generate 3 new edges from the previously defined points via shared_ptr handles:	
	std::shared_ptr<geo_edge2D> e1 = std::make_shared<geo_edge2D>(p1,p2,id_gen_edge());
	std::shared_ptr<geo_edge2D> e2 = std::make_shared<geo_edge2D>(p2,p3,id_gen_edge());
	std::shared_ptr<geo_edge2D> e3 = std::make_shared<geo_edge2D>(p3,p1,id_gen_edge());
	
	//associate the Points with the Edges (for two way association):
	p1->ConEdges.push_back(e1);		p1->ConEdges.push_back(e3);	
	p2->ConEdges.push_back(e1);		p2->ConEdges.push_back(e2);	
	p3->ConEdges.push_back(e2);		p3->ConEdges.push_back(e3);	
	
	//Generate Triangle from Edges via shared_ptr handle:
	std::shared_ptr<geo_triangle2D> tri = std::make_shared<geo_triangle2D>(e1,e2,e3,id_gen_triangle());	
	
	//associate the Points with the Triangle (for two way association):
	p1->ConTriangles.push_back(tri);	p2->ConTriangles.push_back(tri);	p3->ConTriangles.push_back(tri);
	
	//TODO: Pushback of Points in corresponding mesh vectors!
	
	//associate the Edges with the Triangle (for two way association):	
	e1->ConTriangle = tri;	e2->ConTriangle = tri;	e3->ConTriangle = tri;
	
	//associate the Edges to the mesh:
	M_edges.push_back(e1);	M_edges.push_back(e2);	M_edges.push_back(e3);
	
	//associate the Triangle to the mesh:
	M_triangles.push_back(tri);	

	//------------------------------------------------------------------
	//Debug Plotting the triangle:
	tri->plot_me(mat);	//Plotting the triangle onto the canvas
	
	//------------------------------------------------------------------	
	//Debug output:	
	std::cout << "tri id: " << tri->id << std::endl; 
	std::cout << "tri Point      id's:[" << tri->Ptri[0]->id << " , " << tri->Ptri[1]->id << " , " << tri->Ptri[2]->id << "] " << std::endl;
	std::cout << "tri Edge       id's:[" << tri->Etri[0]->id << " , " << tri->Etri[1]->id << " , " << tri->Etri[2]->id << "] " << std::endl;
	std::cout << "tri Edge 1st P id's:[" << tri->Etri[0]->Pedge[0]->id << " , " << tri->Etri[1]->Pedge[0]->id << " , " << tri->Etri[2]->Pedge[0]->id << "] " << std::endl;
	std::cout << "tri Edge 2nd P id's:[" << tri->Etri[0]->Pedge[1]->id << " , " << tri->Etri[1]->Pedge[1]->id << " , " << tri->Etri[2]->Pedge[1]->id << "] " << std::endl;
	
	//------------------------------------------------------------------
	//Summary output:
	std::cout << "\n====================================================" << std::endl;
	std::cout << "mesh summary counters:" << std::endl;
	std::cout << "Number of Points: " << id_point_count << std::endl;
	std::cout << "Number of Edges: " << id_edge_count << std::endl;
	std::cout << "Number of Triangles: " << id_triangle_count << std::endl;
	std::cout << "mesh summary pointer vectors:" << std::endl;
	std::cout << "Number of Points: " << M_points.size() << std::endl;
	std::cout << "Number of Edges: " << M_edges.size() << std::endl;
	std::cout << "Number of Triangles: " << M_triangles.size() << std::endl;
	
	//------------------------------------------------------------------		
}










