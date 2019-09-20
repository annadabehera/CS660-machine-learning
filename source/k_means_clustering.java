import java.util.*;
class point {
	static int n;
	double[]values;
	point(double...v) { values=v; n=v.length; }
	point(point p) {
		values=new double[n];
		System.arraycopy(p.values, 0, values , 0, point.n);
	}
	double distance(point p) {
		double sum=0;
		for(int i=0; i<n; ++i)
			sum+=Math.pow(values[i]-p.values[i],2);
		return Math.sqrt(sum);
	}
	public String toString() {
		String f="(";
		for(int i=0; i<point.n; ++i)
			f+=f.format("%.2f, ", values[i]);
		f+="\b\b) ";
		return f;
	}
}

class cluster {
	point center;
	private static int next_iden=65;
	int identity;
	int n;
	ArrayList<point> in_cluster;
	cluster(point[]points) {
		in_cluster=new ArrayList<point>();
		int rnd=new Random().nextInt()%points.length;
		center=new point(points[Math.abs(rnd)]);
		identity=next_iden++;
		n=0;
	}
	void add(point p)
	{
		++n;
		in_cluster.add(p);
	}
	void calculate_center() {
		if(n==0)	return;
		for(int i=0; i<point.n; ++i) {
			double sum=0;
			for(point p:in_cluster) {
				sum+=p.values[i];
			}
			center.values[i]=sum/n;
		}
	}
	public String toString() {
		String f=new String();
		f=f.format("Cluster %c = ", identity);
		f+=center+ "{\n";
		for(point p:in_cluster) {
			f+="\t"+p+"\n";
		}
		f+="}\n";
		return f;
	}
}

public class k_means_clustering {
	point[]X;
	cluster[]C;
	k_means_clustering(point...p) {
		X=p;
	}
	k_means_clustering(ArrayList<point> p)
	{
		X=p.toArray(X);
	}
	void cluster_into(int k) {
		C=new cluster[k];
		for(int i=0; i<k; ++i)
			C[i]=new cluster(X);
		boolean reassign;
		do {
			/* Calculate the distance between the data points and
			the clusters and assign the points to the clusters.*/
			//if(true) break;
			reassign=false;
			for(point p:X) {
				/* Find the nearest cluster*/
				double small=p.distance(C[0].center);
				cluster near=C[0];
				for(cluster c:C) {
					double dist=p.distance(c.center);
					if(dist<small) {
						near=c;
						small=dist;
					}
				}
				/* Add the point to the cluster */
				if(!near.in_cluster.contains(p)) {
					reassign=true;
					for(cluster c:C)
						c.in_cluster.remove(p);
					near.add(p);
				}
			}

			/* Recalculate the culster center */
			for(cluster c:C) {
				c.calculate_center();
			}
		/* Until no points are reassigned */
		} while(reassign);
	}

	/* Sample program to cluster the points 
	(2,3), (4,5),
	(3,4), (4,3),
	(1,0), (17,18),
	(12,15), (11,14),
	(13, 11), (10, 12)
	into 2 clusters using the K-means clustering. */
	public static void main(String[]args) {
		k_means_clustering kmc;
		kmc=new k_means_clustering(
			new point(2,3), new point(4,5),
			new point(3,4), new point(4,3),
			new point(1,0), new point(17,18),
			new point(12,15), new point(11,14),
			new point(13, 11), new point(10, 12)
			);
		kmc.cluster_into(2);

		java.io.PrintStream STDOUT=System.out;
		for(cluster c:kmc.C) {
			STDOUT.println(c);
		}
	}
}
