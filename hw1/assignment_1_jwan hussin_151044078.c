#include <stdio.h>
/* determine the cordinates of the palne */
#define plane_ax 0
#define plane_ay 0
#define plane_bx 1000
#define plane_by 0
#define plane_cx 1000
#define plane_cy 800
#define plane_dx 0
#define plane_dy 800





void main(void)
	{
		       /* determine the cordinates of the target */
		double tar_ax =200.0,
			   tar_ay =500.0,
			   tar_bx =250.0,
			   tar_by =500.0,
			   tar_cx =250.0,
			   tar_cy =530.0,
			   tar_dx =200.0,
			   tar_dy =530.0,
			   /* determine the length and width of the detector */
			   det_Length =100.0,
			   det_width =50.0;
		int n = 5 ; /* number of steps user can make */
		double x,y;	
			printf("border = [ %d x %d ]  ,  ",(plane_bx - plane_ax),(plane_dy - plane_ay) );
			printf("marked region = [ %.2f x %.2f ]   ,   ",(tar_bx - tar_ax),(tar_dy - tar_ay) );
			printf("Detector = [ %.2f x %.2f ]\n",det_Length,det_width );   
			   		
		   			if ((tar_ax < plane_ax) ||
		   				(tar_ay < plane_ay) ||
		   				(tar_bx > plane_bx) ||
		   				(tar_by < plane_by) ||
		   				(tar_cx > plane_cx) ||
		   				(tar_cy > plane_cy) ||
		   				(tar_dx < plane_dx) ||
		   				(tar_dy > plane_dy))
		   				{
		   					printf("plase chek the cordinates of the plane and the target in the source code\n");
		   					printf("d_______________________c\n");
		   					printf("|                       |\n");
		   					printf("|       d________c      |\n");
		   					printf("|       |        |      |\n");
		   					printf("|       | target |      |\n");
		   					printf("|       |________|      |\n");
		   					printf("|       a        b      |\n");
		   					printf("|          plane        |\n");
		   					printf("|_______________________|\n");
		   					printf("a                       b\n");
		   					printf("yor target is out the palne\n");

			  				return ;
			   			}

			   		else if ((det_Length > (plane_bx - plane_ax)) ||
			 				 (det_width > (plane_dy - plane_ay)))
			  				{
			   					printf("Check the detector lengths\n");
			   					return ;
			   				}
			   		for ( n ; n > 0 ; --n )
			   		{			
			   			printf("locate the center of the dete\n");
			   			printf("the x cordinate x = ");
			   			scanf("%lf",&x);
						printf("the y cordinate y = ");
			   			scanf("%lf",&y);
			   			printf("\n");
			   			/* cheking if the detector is in the plane */
			   			if ((((det_Length / 2) + x) <= plane_bx ) &&
			   				((x - (det_Length / 2)) >= plane_ax ) &&
			   				(((det_width / 2) + y) <= plane_dy ) &&
			   				((y - (det_width / 2)) >= plane_ay ) )
			   				{    
			   					/* if fully overlaps */
			   					if (((x -(det_Length / 2)) <= tar_ax) &&
			   				        (((det_Length / 2) + x) >= tar_bx) &&
			   				        ((y -(det_width / 2)) <= tar_ay) &&
			   				        (((det_width / 2) + y) >= tar_dy) )
			   				    {
			   						printf("you found the target\n");
			   						return ;
			   					}
			   					/* if the target was missed */
			   					else if ((x + (det_Length / 2)) <= tar_ax)
			   						{
			   							printf("you missed the target\n");
			   							printf("you have %d steps\n", n-1 );

			   						}
			   					else if ((x - (det_Length / 2)) >= tar_bx)
			   						{
			   							printf("you missed the target\n");
			   							printf("you have %d steps\n", n-1 );

			   						}
			   					else if ((y + (det_width / 2)) <= tar_ay)
			   						{
			   							printf("you missed the target\n");
			   							printf("you have %d steps\n", n-1 );

			   						}
			   					else if ((y - (det_Length / 2)) >= tar_dy)
			   						{
			   							printf("you missed the target\n");
			   							printf("you have %d steps\n", n-1 );

			   						}
			   						/* if there is a partial overlap */
			   					else if ((x + (det_Length / 2) > tar_ax) &&
			   							 (x + (det_Length / 2) < tar_bx) && 
			   						     (y + (det_width / 2) > tar_ay) &&
			   						     (y + (det_width / 2) < tar_dy))
			   						{
			   							tar_bx = x + (det_Length / 2);
			   							tar_dy = y + (det_width / 2);
			   							tar_cx = x + (det_Length / 2);
			   							tar_cy = y + (det_width / 2);
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   					else if ((x + (det_Length / 2) > tar_ax) &&
			   							 (x + (det_Length / 2) < tar_bx) &&	
			   							 (y - (det_width / 2) < tar_ay) &&
			   						     (y + (det_width / 2) > tar_dy))
			   						{
			   							tar_bx = x + (det_Length / 2);
			   							tar_cx = x + (det_Length / 2); 
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   					else if ((x + (det_Length / 2) > tar_ax) &&	
			   							 (x + (det_Length / 2) < tar_bx) &&
			   							 (y - (det_width / 2) > tar_ay) &&
			   						     (y - (det_width / 2) < tar_dy))
			   						{
			   							tar_ay = y - (det_width / 2);
			   							tar_cx = x + (det_Length / 2);
			   							tar_bx = y - (det_width / 2);
			   							tar_by = x + (det_Length / 2);
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   					else if ((x + (det_Length / 2) > tar_bx) &&
			   							 (x - (det_Length / 2) < tar_ax) &&	
			   							 (y + (det_width / 2) < tar_dy) &&
			   						     (y + (det_width / 2) > tar_ay))
			   						{
			   							tar_dy = y + (det_width / 2);
			   							tar_cy = y + (det_width / 2);
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   					else if ((x + (det_Length / 2) > tar_bx) &&
			   							 (x - (det_Length / 2) < tar_ax) &&	
			   							 (y - (det_width / 2) < tar_dy) &&
			   						     (y - (det_width / 2) > tar_ay))
			   						{
			   							tar_ay = y - (det_width / 2);
			   							tar_by = y - (det_width / 2);
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   					else if ((x - (det_Length / 2) < tar_bx) &&
			   							 (x - (det_Length / 2) > tar_ax) &&	
			   							 (y + (det_width / 2) < tar_cy) &&
			   						     (y + (det_width / 2) > tar_by))
			   						{
			   							tar_ax = x - (det_Length / 2);
			   							tar_cy = y + (det_width / 2);
			   							tar_dx = x - (det_Length / 2);
			   							tar_dy = y + (det_width / 2);
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   					else if ((x - (det_Length / 2) < tar_bx) &&
			   							 (x - (det_Length / 2) > tar_ax) &&	
			   							 (y + (det_width / 2) > tar_cy) &&
			   						     (y - (det_width / 2) < tar_by))
			   						{
			   							tar_ax = x - (det_Length / 2);
			   							tar_dx = x - (det_Length / 2);
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   					else if ((x - (det_Length / 2) < tar_bx) &&
			   							 (x - (det_Length / 2) > tar_ax) &&	
			   							 (y - (det_width / 2) < tar_cy) &&
			   						     (y - (det_width / 2) > tar_by))
			   						{
			   							tar_dx = x - (det_Length / 2);
			   							tar_by = y - (det_width / 2);
			   							tar_ax = x - (det_Length / 2);
			   							tar_ay = y - (det_width / 2);
			   							det_Length = det_Length /2;
			   							det_width = det_width /2;
			   							printf(" your target and detectors size have been updated \n");
			   							printf(" you have %d steps\n", n-1 );

			   						}
			   						

			   				}
			   			else 
			   				{
			   					printf("yor detector is out the plane\n");
			   					n++;
			   				}

			   		}




	}