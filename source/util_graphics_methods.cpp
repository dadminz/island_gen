
//-----------------------------------------------------
// Utility graphics methodes
// 
//-----------------------------------------------------

void plot_line_grid(const cv::Mat &mat,const int &spacing_x, const int &spacing_y,const int &div_major, const cv::Scalar &color, const int &linesize)
{
	for(int iy = 0 ; iy <= (int)mat.rows ; iy = iy + spacing_y)
	{
		for(int ix = 0 ; ix <= (int)mat.cols ; ix = ix + spacing_x)
		{

			if( (ix%div_major == 0) && (iy%div_major == 0) )
			{
				cv::circle(mat, cv::Point(ix,iy), linesize*2, color*2, CV_FILLED, CV_FILLED );
				//cv::circle(mat, cv::Point(ix,iy), linesize, color, CV_FILLED, CV_FILLED );				
			}
			else
			{
				cv::circle(mat, cv::Point(ix,iy), linesize, color, CV_FILLED, CV_FILLED );				
			}		
		}
	}
}
