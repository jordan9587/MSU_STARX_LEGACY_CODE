//Band pass butterworth filter order=2 alpha1=2.5 alpha2=25 
class  FilterBuBp2
{
	public:
		FilterBuBp2()
		{
			for(int i=0; i <= 4; i++)
				v[i]=0.0;
		}
	private:
		float v[5];
	public:
		float step(float x) //class II 
		{
			v[0] = v[1];
			v[1] = v[2];
			v[2] = v[3];
			v[3] = v[4];
			v[4] = (1.000000000000000444e+0 * x)
				 + (-1.00000000000000088818 * v[0])
				 + (0.00000000000000088818 * v[1])
				 + (2.00000000000000088818 * v[2])
				 + (-0.00000000000000088818 * v[3]);
			return 
				 (v[0] + v[4])
				- 2 * v[2];
		}
};

