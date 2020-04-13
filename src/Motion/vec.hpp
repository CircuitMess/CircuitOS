#ifndef MOTION_VEC_H
#define MOTION_VEC_H

/** ### vec3 ### */

template<typename T>
union vec3 {
	struct { T x, y, z; };
	struct { T r, g, b; };
	struct { T pitch, yaw, roll; };

	vec3<T>(T x, T y, T z) : x(x), y(y), z(z){ }
	vec3<T>() : x(0), y(0), z(0){ }

	T& operator[](int i){
		if(i > 2) throw std::exception();
		return reinterpret_cast<T*>(this)[i];
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
		if(i > 3) throw std::exception();
		return reinterpret_cast<T*>(this)[i];
	}
};

typedef vec4<float> vec4f;
typedef vec4<double> vec4d;
typedef vec4<uint> vec4u;
typedef vec4<int> vec4i;

#endif //MOTION_VEC_H
