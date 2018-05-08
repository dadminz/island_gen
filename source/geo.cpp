//######################################################################
//2D Point
geo_point2D::geo_point2D(float tx, float ty,int tid)
{
	std::cout << "calling constructor geo_point2D(ID:"<< tid << " x:" << tx << " iy:" << ty << ")" << std::endl;
	x = tx;
	y = ty;
	id = tid;
}

cv::Point2f geo_point2D::cvp2f()
{
	//returns the Point coords as a cv::Point2f object
	return cv::Point2f(x,y);
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

void geo_mesh2D::plot_me(cv::Mat &mat)
{
	for (std::vector<std::shared_ptr<geo_point2D>>::iterator it = M_points.begin(); it != M_points.end(); ++it)
	{
		
		cv::circle(mat, (*it)->cvp2f(), 3, cv::Scalar(0,0,255), CV_FILLED, CV_FILLED );
		cv::putText(mat, std::to_string((*it)->id) , (*it)->cvp2f(), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255,255,255), 1);
	}	
	
	for (std::vector<std::shared_ptr<geo_triangle2D>>::iterator it = M_triangles.begin(); it != M_triangles.end(); ++it)
	{		
		(*it)->plot_me(mat);
	}		
}

void geo_mesh2D::triangle_generator(std::shared_ptr<geo_point2D> p1,std::shared_ptr<geo_point2D> p2,std::shared_ptr<geo_point2D> p3)
{

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
	
	//associate the Edges with the Triangle (for two way association):	
	e1->ConTriangle = tri;	e2->ConTriangle = tri;	e3->ConTriangle = tri;
	
	//associate the Edges to the mesh:
	M_edges.push_back(e1);	M_edges.push_back(e2);	M_edges.push_back(e3);
	
	//associate the Triangle to the mesh:
	M_triangles.push_back(tri);	
	
	
}

void geo_mesh2D::point_grid_generator(int count_x, int count_y, float dx, float dy)
{	
	//function for Generating a Grid of Points in the mesh structure.
	std::cout << "calling geo_mesh2D.point_grid_generator(count_x: "<< count_x <<" count_y: " << count_y << ")" << std::endl;
	int ix = 0;
	int iy = 0;
	int index = 0;
	float offset_x = 100;
	float offset_y = 100;
	
	for(iy = 0 ; iy < count_y ; iy++)
	{
		for(ix = 0 ; ix < count_x ; ix++)
		{
			std::shared_ptr<geo_point2D> P = std::make_shared<geo_point2D>(ix*dx+offset_x , iy*dy+offset_y , id_gen_point());
			M_points.push_back(P);
		}
	}	
}

void geo_mesh2D::point_grid_triangulator(int count_x, int count_y)
{
	std::cout << "calling geo_mesh2D.point_grid_triangulator(count_x: "<< count_x <<" count_y: " << count_y << ")" << std::endl;
	
	int ix = 0;
	int iy = 0;
	int index = 0;	
	float rng = 0;
	
	std::uniform_real_distribution<float> distribution_rng(0,1);
	
	for(iy = 0 ; iy < count_y - 1 ; iy++)
	{
		for(ix = 0 ; ix < count_x -1 ; ix++)
		{
			//The 4 point cursor is not allowed to go out of bounds of the grid !
			//	p1--p2	
			//	 |	|
			//	p3--p4
			index = iy*count_x + ix;
			std::shared_ptr<geo_point2D> p1 = M_points[index];
			std::shared_ptr<geo_point2D> p2 = M_points[index+1];
			std::shared_ptr<geo_point2D> p3 = M_points[index+count_x];
			std::shared_ptr<geo_point2D> p4 = M_points[index+count_x+1];
			
			rng = distribution_rng(RandGenerator);
			
			if(rng > 0.5)
			{
				triangle_generator(p1,p2,p3);
				triangle_generator(p2,p4,p3);
			}else{				
				triangle_generator(p1,p2,p4);
				triangle_generator(p1,p4,p3);				
			}			
		}
	}		
}

void geo_mesh2D::point_grid_DeformerRand(int count_x, int count_y,float dx ,float dy)
{
	std::cout << "calling geo_mesh2D.point_grid_DeformerRand (count_x: "<< count_x <<" count_y: " << count_y << ")" << std::endl;
	
	int ix = 0;
	int iy = 0;
	int index = 0;	
	float rng_x = 0;
	float rng_y = 0;
	
	std::uniform_real_distribution<float> distribution_rng_x(-dx,+dx);
	std::uniform_real_distribution<float> distribution_rng_y(-dy,+dy);
	
	for(iy = 1 ; iy < count_y - 1 ; iy++)
	{
		for(ix = 1 ; ix < count_x -1 ; ix++)
		{
			//The point cursor is not allowed to go out of bounds of the grid with padding around it:!
			//0000000
			//0111110
			//0111110	
			//0000000
			
			rng_x = distribution_rng_x(RandGenerator);
			rng_y = distribution_rng_y(RandGenerator);
			
			index = iy*count_x + ix;
			M_points[index]->x = M_points[index]->x + rng_x;		
			M_points[index]->y = M_points[index]->y + rng_y;		
		}
	}	
}

void geo_mesh2D::summary()
{
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










