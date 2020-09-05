#ifndef MOTION_VEC_H
#define MOTION_VEC_H

#define die() exit(1)
// #define die() throw std::exception()

/** ### vec3 ### */

template<typename T>
union vec3 {
	struct { T x, y, z; };
	struct { T r, g, b; };
	struct { T pitch, yaw, roll; };

	vec3<T>(T x, T y, T z) : x(x), y(y), z(z){ }
	vec3<T>() : x(0), y(0), z(0){ }
	vec3<T>(std::initializer_list<T> data){
		if(data.size() > 3) die();
		int i = 0;
		for(T d : data){
			reinterpret_cast<T*>(this)[i++] = d;
		}
	}

	T& operator[](int i){
		if(i > 2) die();
		return reinterpret_cast<T*>(this)[i];
	}

	// https://stackoverflow.com/questions/31258811/in-c-template-copy-assignment-operator-not-compatible-with-initializer-list
	vec3& operator=(T const(&other)[3]){
		x = other[0];
		y = other[1];
		z = other[2];
		return *this;
	}

	vec3<T> operator+=(T val){
		x += val;
		y += val;
		z += val;
		return *this;
	}

	vec3<T> operator*=(T val){
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	vec3<T> operator+=(const vec3<T>& other){
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3<T> operator*=(const vec3<T>& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3<T> operator+(T val){
		return { x + val, y + val, z + val };
	}

	vec3<T> operator-(T val){
		return { x - val, y - val, z - val };
	}

	vec3<T> operator*(T val){
		return { x * val, y * val, z * val };
	}

	vec3<T> operator+(const vec3<T>& other){
		return { x + other.x, y + other.y, z + other.z };
	}

	vec3<T> operator-(const vec3<T>& other){
		return { x - other.x, y - other.y, z - other.z };
	}

	vec3<T> operator*(const vec3<T>& other){
		return { x * other.x, y * other.y, z * other.z };
	}

	T len(){
		return sqrt(x*x + y*y + z*z);
	}

	T angleCos(const vec3<T>& other){
		return dot(other) / (len() * other.len());
	}

	T dot(const vec3<T>& other){
		return x * other.x + y * other.y + z * other.z;
	}

	vec3<T> cross(const vec3<T>& other){
		return {
			y * other.z - z * other.y,
			x * other.z - z * other.x,
			x * other.y - y * other.x
		};
	}
};

typedef vec3<float> vec3f;
typedef vec3<double> vec3d;
typedef vec3<uint> vec3u;
typedef vec3<int> vec3i;

/** ### vec4 ### */

template<typename T>
union vec4 {
	struct { T x, y, z, w; };
	struct { T r, g, b, a; };

	vec4<T>(T x, T y, T z, T w) : x(x), y(y), z(z), w(w){ }
	vec4<T>() : x(0), y(0), z(0), w(0){ }

	T& operator[](int i){
		if(i > 3) die();
		return reinterpret_cast<T*>(this)[i];
	}
};

typedef vec4<float> vec4f;
typedef vec4<double> vec4d;
typedef vec4<uint> vec4u;
typedef vec4<int> vec4i;

/** ### quat ### */

/**
 * https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @tparam T
 */
template<typename T>
struct quat {
	T w, x, y, z;

	quat<T>(T w, T x, T y, T z) : w(w), x(x), y(y), z(z){ }
	quat<T>(T w, const vec3<T>& vec) : w(w), x(vec.x), y(vec.y), z(vec.z){ }
	quat<T>() : w(0), x(0), y(0), z(0){ }

	quat<T>(vec3<T> euler){
		float cy = cos(euler.yaw * 0.5f);
		float sy = sin(euler.yaw * 0.5f);
		float cp = cos(euler.pitch * 0.5f);
		float sp = sin(euler.pitch * 0.5f);
		float cr = cos(euler.roll * 0.5f);
		float sr = sin(euler.roll * 0.5f);

		w = cr * cp * cy + sr * sp * sy;
		x = sr * cp * cy - cr * sp * sy;
		y = cr * sp * cy + sr * cp * sy;
		z = cr * cp * sy - sr * sp * cy;
	}

	quat<T> inverse(){
		return { w, -x, -y, -z };
	}

	vec3<T> euler() const{
		vec3<T> euler;
		float q[4] = { w, x, y, z };

		euler.pitch  = -atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
		euler.yaw = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);
		euler.roll = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));

		return euler;

		// roll (x-axis rotation)
		float sinr_cosp = 2 * (w * x + y * z);
		float cosr_cosp = 1 - 2 * (x * x + y * y);
		euler.roll = std::atan2(sinr_cosp, cosr_cosp);
		
		// pitch (y-axis rotation)
		float sinp = 2 * (w * y - z * x);
		if (abs(sinp) >= 1)
			euler.pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
		else
			euler.pitch = std::asin(sinp);

		// yaw (z-axis rotation)
		float siny_cosp = 2 * (w * z + x * y);
		float cosy_cosp = 1 - 2 * (y * y + z * z);
		euler.yaw = std::atan2(siny_cosp, cosy_cosp);

		return euler;
	}

	vec3<T> rotate(const vec3<T>& point) const {
		vec3<T> q = { x, y, z };
		vec3<T> p = point;
		return p * (float) pow(w, 2) + q.cross(p) * w + q * p.dot(q) + q.cross(p) * w + q.cross(q.cross(p));
	}
};

typedef quat<float> quatf;

#endif //MOTION_VEC_H
