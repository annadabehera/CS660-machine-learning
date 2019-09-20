/* The points are vectors in n-dimensional space 
 * n       is the number of dimension
 * val     is the projection of the point in any dimension
 * class   is the class/label of the point
 * 
 * stdio.h needed for datatypes and printing to the STDOUT
 */
#include<stdio.h>
typedef int class;
struct point_t { size_t n; double * val; class c; };

/* Calculate the Euclidean distance between any two points.
 * math.h for power and square roots
 */
#include<math.h>
double euclid(struct point_t * p1, struct point_t * p2)
{
	double dist = 0, v1, v2;
	size_t n=p1->n>p2->n?p1->n:p2->n;
	for(size_t i=0; i<n; ++i) {
		v1=n>p1->n?0:p1->val[i];
		v2=n>p2->n?0:p2->val[i];
		dist+=pow(v1-v2,2);
	}
	return sqrt(dist);
}

class nearest_neighbor(struct point_t ** points,
		       size_t n, struct point_t * p)
/* points is all the points already classified
 * n      total number of all the points
 * p      point that is to be classified
 */
{
	double near = euclid(points[0], p);
	class c = points[0]->c;

	for(size_t i=1; i<n; ++i) {
		double dist=euclid(points[i], p);
		if(dist<near) {
			near=dist;
			c=points[i]->c;
		}
	};
	return p->c=c;
}

class k_nearest_neighbor(struct point_t ** points,
			 size_t n, size_t k,
			 struct point_t * p)
/* points is all the points already classified
 * n      total number of all the points
 * k      total number of neighbor to poll from
 * p      point that is to be classified
 */
{
	if(n<=k) { return nearest_neighbor(points, n, p); }

	double small, dist;
	struct point_t * near[k], * tmp;

	for(size_t i=0; i<k; ++i)
		near[i]=points[i];


	for(size_t i=0; i<n; ++i) {
		dist=euclid(p, points[i]);
		for(size_t j=0;j<k; ++j) {
			if(dist<euclid(p, near[j])) {
				near[j]=points[i];
				break;
			}
		}
	}

	size_t count=0, max=0;
	for(size_t i=0; i<k; ++i) {
		for(size_t j=0; j<k; ++j)
			if(near[i]->c==near[j]->c)
				++count;
		if(count>max) {
			max=count;
			tmp = near[i];
		}

	}
	return p->c=tmp->c;
}

/* Sample run 
 * There are six 2D data points:
	 * (2, 4), (3, 8), (1, 5) in class 'A'
	 * (8, 3), (9, 6), (7, 7) in class 'B'
 * A unknown point (5,5) is to be classified.
 */

int main(void)
{
	size_t n=6;
	struct point_t * points[] = {
		&(struct point_t){.n=2, .val=(double[]){2,4}, .c='A'},
		&(struct point_t){.n=2, .val=(double[]){3,8}, .c='A'},
		&(struct point_t){.n=2, .val=(double[]){1,5}, .c='A'},
		&(struct point_t){.n=2, .val=(double[]){8,2}, .c='B'},
		&(struct point_t){.n=2, .val=(double[]){9,6}, .c='B'},
		&(struct point_t){.n=2, .val=(double[]){7,7}, .c='B'}
	},
	* unknown = &(struct point_t){.n=2, .val=(double[]){5,5}, .c='?'};
	for(size_t i=0; i<n; ++i)
		printf("Distance from (%g, %g) to (%g, %g, %c) =  %g\n",
			unknown->val[0], unknown->val[1],
			points[i]->val[0], points[i]->val[1], points[i]->c,
			euclid(unknown, points[i]));
	printf("\nThe unknown point belongs to class: \n");
	printf("\t(using nearest neighbor): %c\n",
		nearest_neighbor(points, 6, unknown));
	printf("\t(using 3-nearest neighbor): %c\n",
		k_nearest_neighbor(points, 6, 3, unknown));
	return 0;
}
