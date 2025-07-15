#pragma once
#include <cmath>
#include <windows.h>

#define M_PI 3.14159265358979323846

using namespace std;

[swap_blocks]
[block]
struct cs_vector {
	[swap_blocks]
	[block]

	[swap_lines]
	cs_vector();
	cs_vector(float, float, float);
	cs_vector(const cs_vector &);

	float size() const;

	float operator*(const cs_vector &) const;
	[/swap_lines]

	[/block]

	[block]
	float m_x;
	float m_y;
	float m_z;
	[/block]
	[/swap_blocks]
};
[/block]

[block]
struct cs_vector;
struct bone_vector {
	[swap_blocks]
	[block]
	cs_vector unpad() const;
	[/block]

	[block]
	float m_x;
	unsigned char unk1[0xC];
	float m_y;
	unsigned char unk2[0xC];
	float m_z;
	[/block]
	[/swap_blocks]
};
[/block]

[block]
struct view_vector {
	[swap_blocks]
	[block]

	[swap_lines]
	view_vector();
	view_vector(float, float);
	view_vector(const view_vector &);

	view_vector & operator*=(const float &);

	view_vector & operator+=(const view_vector &);

	view_vector operator-(const view_vector &) const;

	view_vector operator/(const float &) const;

	bool clamp(bool);

	view_vector get_aura(float) const;

	view_vector get_box(float) const;

	void anti_kick();
	[/swap_lines]

	[/block]

	[block]
	float m_x;
	float m_y;
	[/block]
	[/swap_blocks]
};
[/block]
[/swap_blocks]

[junk_enable 40 360 /]


[swap_blocks]
[block]
cs_vector::cs_vector() {
[add_junk 120 1000 /]
	[swap_lines]
	m_x = 0.f;
	m_y = 0.f;
	m_z = 0.f;
	[/swap_lines]
}
[/block]

[block]
cs_vector::cs_vector(float x, float y, float z) {
[add_junk 120 1000 /]
	[swap_lines]
	m_x = x;
	m_y = y;
	m_z = z;
	[/swap_lines]
}
[/block]

[block]
cs_vector::cs_vector(const cs_vector & x) : m_x(x.m_x), m_y(x.m_y), m_z(x.m_z) {
[add_junk 120 1000 /]
	[swap_lines]
	m_x = x.m_x;
	m_y = x.m_y;
	m_z = x.m_z;
	[/swap_lines]
}
[/block]

[block]
float cs_vector::size() const {
[add_junk 120 1000 /]
	return sqrt((m_x * m_x) + (m_y * m_y));
}
[/block]

[block]
float cs_vector::operator*(const cs_vector & arg) const {
[add_junk 120 1000 /]
	return sqrt((m_x - arg.m_x)*(m_x - arg.m_x) + (m_y - arg.m_y)*(m_y - arg.m_y) + (m_z - arg.m_z)*(m_z - arg.m_z));
}
[/block]

[block]
cs_vector bone_vector::unpad() const {
[add_junk 120 1000 /]
	return cs_vector(m_x, m_y, m_z + 3.f);
}
[/block]

[block]
view_vector::view_vector() {
[add_junk 120 1000 /]
	[swap_lines]
	m_x = 0.f;
	m_y = 0.f;
	[/swap_lines]
}
[/block]

[block]
view_vector::view_vector(float x, float y) {
[add_junk 120 1000 /]
	[swap_lines]
	m_x = x;
	m_y = y;
	[/swap_lines]
}
[/block]

[block]
view_vector::view_vector(const view_vector & x) {
[add_junk 120 1000 /]
	[swap_lines]
	m_x = x.m_x;
	m_y = x.m_y;
	[/swap_lines]
}
[/block]

[block]
view_vector & view_vector::operator*=(const float & arg) {
[add_junk 120 1000 /]
	[swap_lines]
	m_x *= arg;
	m_y *= arg;
	[/swap_lines]

	return *this;
}
[/block]

[block]
view_vector & view_vector::operator+=(const view_vector & arg) {
[add_junk 120 1000 /]
	[swap_lines]
	m_x += arg.m_x;
	m_y += arg.m_y;
	[/swap_lines]

	return *this;
}
[/block]

[block]
view_vector view_vector::operator-(const view_vector & arg) const {
[add_junk 120 1000 /]
	return view_vector(m_x - arg.m_x, m_y - arg.m_y);
}
[/block]

[block]
view_vector view_vector::operator/(const float & arg) const {
[add_junk 120 1000 /]
	return view_vector(m_x / arg, m_y / arg);
}
[/block]

[block]
bool view_vector::clamp(bool aim = false) {
[add_junk 120 1000 /]
	if (!isfinite(m_x) || !isfinite(m_y)) {
[add_junk 120 1000 /]
		[swap_lines]
		m_x = 0.f;
		m_y = 0.f;
		[/swap_lines]

		return false;
	}
[add_junk 120 1000 /]

	[swap_blocks]
	[block]
	while (m_y < -180.0f) {
[add_junk 120 1000 /]
		m_y += 360.0f;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	while (m_y > 180.0f) {
[add_junk 120 1000 /]
		m_y -= 360.0f;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (m_x > 88.0f) {
[add_junk 120 1000 /]
		m_x = 88.0f;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (m_x < -88.0f) {
[add_junk 120 1000 /]
		m_x = -88.0f;
	}
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]

	if (aim) {
		m_y += 360.0f;
	}

	return true;
}
[/block]

[block]
view_vector view_vector::get_aura(float distance) const {
[add_junk 120 1000 /]

	return view_vector(3.f * distance * sin(fabs(m_x) * M_PI / 360.f), 3.f * distance * sin(fabs(m_y) * M_PI / 360.f));
}
[/block]

[block]
view_vector view_vector::get_box(float distance) const {
[add_junk 120 1000 /]
	return view_vector(distance * sin(m_x * M_PI / 360.f), distance * sin(m_y * M_PI / 360.f));
}
[/block]

[block]
void view_vector::anti_kick() {
	[swap_blocks]
	[block]
	if (m_x > 37.f) {
[add_junk 120 1000 /]
		m_x = 37.f;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (m_x < -37.f) {
[add_junk 120 1000 /]
		m_x = -37.f;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (m_y > 37.f) {
[add_junk 120 1000 /]
		m_y = 37.f;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (m_y < -37.f) {
[add_junk 120 1000 /]
		m_y = -37.f;
	}
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]
}
[/block]
[/swap_blocks]


















view_vector calc_ang(const cs_vector & src, const cs_vector & dst, const cs_vector & my_punch, const cs_vector & my_orig) {
	float delta[3] = { (src.m_x - dst.m_x), (src.m_y - dst.m_y), (src.m_z + my_orig.m_z - dst.m_z) };
	float hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

	view_vector view_angle(atanf(delta[2] / hyp) * (180 / M_PI) - my_punch.m_x * 2.f, atanf(delta[1] / delta[0]) * (180 / M_PI) - my_punch.m_y * 2.f);
	if (delta[0] >= 0.f) {
		view_angle.m_y += 180.0f;
	}

	view_angle.clamp();

	return view_angle;
}