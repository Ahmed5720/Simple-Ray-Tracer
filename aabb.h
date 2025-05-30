#ifndef AABB_H
#define AABB_H

class aabb{
	public:
		interval x,y,z;

		aabb() {} // no default aabb

		aabb(const interval& x, const interval& y, const interval& z)
		: x(x), y(y), z(z) {}

		// first make sure a < b if not flip it.
		aabb(const point3& a, const point3& b)
		{
			 x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
        	y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
        	z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
		}

		aabb(const aabb& box0, const aabb& box1)
		{
			x = interval(box0.x,box1.x);
			y = interval(box0.y,box1.y);
			z = interval(box0.z,box1.z);
		}

		//define axis
		const interval& axis_interval(int n) const {
			if (n == 1) return y;
        	if (n == 2) return z;
        	return x;
		}

		int longest_axis() const {
			//returns index of the longest axis

			return x.size() > y.size() ? (x.size() > z.size() ? 0:2) : (y.size() > z.size() ? 1 : 2); 
		}

		bool hit(const ray& r, interval ray_t) const{
		const point3& ray_orig = r.origin();
		const vec3& ray_dir = r.direction();

			//check if ray is within all three intervals
			// note ray = p(x) = orig + t * dir
			// i.e t0 = x0 - orig * (1/dir)
			for (int axis = 0; axis < 3; axis++)
			{
				const interval& ax = axis_interval(axis);
            	const double adinv = 1.0 / ray_dir[axis];

            	auto t0 = (ax.min - ray_orig[axis])	* adinv;
            	auto t1 = (ax.max - ray_orig[axis])	* adinv;
            	if (t0 < t1) {
                	if (t0 > ray_t.min) ray_t.min = t0;
                	if (t1 < ray_t.max) ray_t.max = t1;
	            }
	            else
	            {
	                if (t1 > ray_t.min) ray_t.min = t1;
	                if (t0 < ray_t.max) ray_t.max = t0;
	            }

	            if (ray_t.max <= ray_t.min)
	                return false;
			}
			return true;
		}

		static const aabb empty, universe;

};


const aabb aabb::empty = aabb(interval::empty, interval::empty, interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);
#endif