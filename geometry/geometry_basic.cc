#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>

using Number = double;

constexpr Number EPS = 1e-10;
constexpr Number INF = 1e10;
const Number PI = acos(-1.0);

inline int sign(Number x) { return (x < -EPS) ? -1 : (x > EPS) ? +1 : 0; }
inline bool equal(Number a, Number b) { return sign(a - b) == 0; }

// change between degree and radian
inline Number to_radian(const Number degree) { return degree * PI / 180.0; }
inline Number to_degree(const Number radian) { return radian * 180.0 / PI; }

/**
 * Point in two dimensional
 */
struct Point {
    Number x, y;

    Point() {}
    Point(Number x, Number y) : x(x), y(y) {}

    // Arithmetic operator between points
    Point operator+(const Point &rhs) const {
        return Point(this->x + rhs.x, this->y + rhs.y);
    }
    Point operator-(const Point &rhs) const {
        return Point(this->x - rhs.x, this->y - rhs.y);
    }
    Point operator*(const Point &rhs) const { // cross product between points
        return Point(this->x * rhs.x - this->y * rhs.y,
                     this->x * rhs.y + this->y * rhs.x);
    }

    // Unary operator and compound assignment operator
    Point operator-() const {
        return Point(-this->x, -this->y);
    }
    Point& operator+=(const Point &rhs) {
        return *this = *this + rhs;
    }
    Point& operator-=(const Point &rhs) {
        return *this = *this - rhs;
    }

    // Arithmetic operator between point and number
    Point operator*(Number rhs) const {
        return Point(this->x * rhs, this->y * rhs);
    }
    Point operator/(Number rhs) const {
        return Point(this->x / rhs, this->y / rhs);
    }

    // Comparison operation
    bool operator==(const Point &rhs) const {
        return sign(this->x - rhs.x) == 0 && sign(this->y - rhs.y) == 0;
    }
    bool operator<(const Point &rhs) const {
        return (this->x < rhs.x) || (this->x == rhs.x && this->y < rhs.y);
    }

    // Other operator
    Number abs(void) const {
        return sqrt(this->x * this->x + this->y * this->y);
    }
    Number abs2(void) const {
        return this->x * this->x + this->y * this->y;
    }
    Number arg(void) const {
        return atan2(this->y, this->x);
    }
    Number dot(const Point &rhs) {
        return this->x * rhs.x + this->y * rhs.y;
    }
    Point rotate90(void) const {
        return Point(-this->y, this->x);
    }
    Point rotate(double angle) const {
        return Point(cos(angle) * this->x - sin(angle) * this->y,
                     sin(angle) * this->x + cos(angle) * this->y);
    }
};
inline Number dot(const Point &p1, const Point &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}
inline Number abs_cross(const Point &p1, const Point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}
// Output of a point
std::ostream& operator<<(std::ostream &os, const Point &p) {
    return os << p.x << ' ' << p.y;
}
// Input of a point
std::istream& operator>>(std::istream &is, Point &p) {
    return is >> p.x >> p.y;
}

// Counter-Clockwise predicate (a, b, c)
enum CCW {
    COUNTER_CLOCKWISE = 1,      // counter clockwise
    CLOCKWISE         = -1,     // clockwise
    ONLINE_FRONT      = 2,      // a--b--c on line
    ONLINE_BACK       = -2,      // c--a--b on line
    ON_SEGMENT        = 0,     // a--c--b on line
    OTHER             = -3,
};

CCW ccw(const Point &a, Point b, Point c) {
    b -= a;  c -= a;
    if (sign(abs_cross(b, c)) == 1) return COUNTER_CLOCKWISE;
    if (sign(abs_cross(b, c)) == -1) return CLOCKWISE;
    if (sign(dot(b, c)) == -1)       return ONLINE_BACK;
    if (sign(b.abs2() - c.abs2()) == -1)   return ONLINE_FRONT;
    return ON_SEGMENT;
}


/**
 * Line in two dimensional
 */
class Line : public std::array<Point, 2> {
public:
    Line() {}
    Line(const Point &p1, const Point &p2) {
        (*this)[0] = p1;
        (*this)[1] = p2;
    }
};

// Input of a line
std::istream& operator>>(std::istream &is, Line &l) {
    return is >> l[0] >> l[1];
}

// Output of a line
std::ostream& operator<<(std::ostream &os, const Line &l) {
    return os << l[0] << ' ' << l[1];
}

inline CCW ccw(const Line &l, const Point &p) {
    return ccw(l[0], l[1], p);
}


/**
 * Segment in two dimensional
 */
class Segment : public Line {
public:
    Segment() {}
    Segment(const Point &p1, const Point &p2) : Line(p1, p2) {}
};


/**
 * Circle in two dimensional
 */
class Circle : public Point {
public:
    Number r;
    Circle() {}
    Circle(const Point &p, Number r = 0.0) : Point(p), r(r) {}
};

// Input of a circle
std::istream& operator>>(std::istream &is, Circle &c) {
    return is >> c.x >> c.y >> c.r;
}



/**
 * Intersection testing
 */
Point Projection(const Line &l, const Point &p) {
    Point dir = l[1] - l[0];
    Number t = dot(p - l[0], dir) / dir.abs2();
    return l[0] + dir * t;
}

inline Point Reflection(const Line &l, const Point &p) {
    return Projection(l, p) * 2.0 - p;
}

inline bool IsOrthogonal(const Line &l1, const Line &l2) {
    return equal(dot(l1[0] - l1[1], l2[0] - l2[1]), 0.0);
}

inline bool IsParallel(const Line &l1, const Line &l2) {
    return equal(abs_cross(l1[0] - l1[1], l2[0] - l2[1]), 0.0);
}

inline bool IsIntersect(const Line &l, const Point &p) {
    return std::abs(ccw(l[0], l[1], p)) != 1;
}

inline bool IsIntersect(const Segment &s, const Point &p) {
    return ccw(s[0], s[1], p) == ON_SEGMENT;
}

inline bool IsIntersect(const Line &l1, const Line l2) {
    return !IsParallel(l1, l2) || IsParallel(l1, Line(l1[0], l2[0]));
}

inline bool IsIntersect(const Line &l, const Segment &s) {
    return sign(abs_cross(l[1] - l[0], s[0] - l[0]) *
                abs_cross(l[1] - l[0], s[1] - l[0])) <= 0;
}

inline bool IsIntersect(const Segment &s1, const Segment &s2) {
    return ccw(s1[0], s1[1], s2[0]) * ccw(s1[0], s1[1], s2[1]) <= 0 &&
        ccw(s2[0], s2[1], s1[0]) * ccw(s2[0], s2[1], s1[1]) <= 0;
}

inline bool IsIntersect(const Circle &c, const Point &p) { // p is in interior or boundary
    return (c - p).abs() <= c.r + EPS;
}

inline bool IsIntersect(const Circle &c, const Line &l) {
    return IsIntersect(c, Projection(l, c));
}

inline bool IsIntersect(const Circle &c1, const Circle &c2) {
    return sign(c1.r + c2.r - (c1 - c2).abs()) >= 0 &&
        sign((c1 - c2).abs() - std::abs(c1.r - c2.r) >= 0);
}


/**
 * Distance and Intersection point
 */
inline Number Distance(const Point &p1, const Point &p2) {
    return (p1 - p2).abs();
}

inline Number Distance(const Line &l, const Point &p) {
    return (p - Projection(l, p)).abs();
}

inline Number Distance(const Segment &s, const Point &p) {
    if (sign(dot(s[1] - s[0], p - s[0])) == -1) return (p - s[0]).abs();
    if (sign(dot(s[0] - s[1], p - s[1])) == -1) return (p - s[1]).abs();
    return (p - Projection(s, p)).abs();
}

inline Number Distance(const Line &l1, const Line &l2) {
    return IsIntersect(l1, l2) ? 0 : Distance(l1, l2[0]);
}

inline Number Distance(const Line &l, const Segment &s) {
    if (IsIntersect(l, s)) return 0.0;
    return std::min(Distance(l, s[0]), Distance(l, s[1]));
}

inline Number Distance(const Segment &s1, const Segment &s2) {
    if (IsIntersect(s1, s2)) return 0.0;
    return std::min({Distance(s1, s2[0]), Distance(s1, s2[1]),
                Distance(s2, s1[0]), Distance(s2, s1[1])});
}

Point CrossPoint(const Line &l1, const Line &l2) {
    Number A = abs_cross(l1[1] - l1[0], l2[1] - l2[0]);
    Number B = abs_cross(l1[1] - l1[0], l1[1] - l2[0]);
    if (sign(std::abs(A)) == -1 && sign(std::abs(B)) == -1) return l2[0];
    if (sign(std::abs(A)) == -1) assert(false);
    return l2[0] + (l2[1] - l2[0]) * B / A;
}

std::vector<Point> CrossPoint(const Circle &c, const Line &l) {
    if (!IsIntersect(c, l))
        return std::vector<Point>();
    Point mid = Projection(l, c);
    if (equal((c - mid).abs(), c.r))
        return {mid};

    Point e = (l[1] - l[0]) / (l[1] - l[0]).abs();
    Number len = sqrt(c.r * c.r - (mid - c).abs2());
    return {mid + e * len, mid - e * len};
}

std::vector<Point> CrossPoint(const Circle &c1, const Circle &c2) {
    if (!IsIntersect(c1, c2))
        return std::vector<Point>();
    Number d = Distance(c1, c2);
    Number r1_cos = (d * d + c1.r * c1.r - c2.r * c2.r) / (2.0 * d);
    Number h = sqrt(c1.r * c1.r - r1_cos * r1_cos);
    Point base = c1 + (c2 - c1) * r1_cos / d;
    Point dir = (c2 - c1).rotate90() * h / d;
    if (dir == Point(0, 0))
        return {base};
    return {base + dir, base - dir};
}


// the tangent line from a point to a circle
std::vector<Point> TangentPoint(const Circle &c, const Point &p) {
    Number x = (p - c).abs2();
    Number d = x - c.r * c.r;
    if (sign(d) == -1) // no point
        return std::vector<Point>();
    d = std::max(d, 0.0);
    Point q1 = (p - c) * (c.r * c.r / x);
    Point q2 = ((p - c) * (-c.r * sqrt(d) / x)).rotate90();
    if (q2 == Point(0, 0)) return {c + q1};
    return {c + q1 - q2, c + q1 + q2};
}

// common tangent lines to two circles
std::vector<Line> CommonTangent(const Circle &c1, const Circle &c2) {
    // two circle contact one point internally
    if (equal(Distance(c1, c2), std::abs(c1.r - c2.r))) { // |  $ $|
        Point cross_point = CrossPoint(c1, c2)[0];
        Point up = (cross_point - c1).rotate90();
        return {Line(cross_point + up, cross_point - up)};
    }

    std::vector<Line> list;

    // caluculate outer tangent
    if (equal(c1.r, c2.r)) {
        Point dir = c2 - c1;
        dir = (dir * (c1.r / dir.abs())).rotate90();
        list.emplace_back(Line(c1 + dir, c2 + dir));
        list.emplace_back(Line(c1 - dir, c2 - dir));
    }
    else {
        Point p = (c1 * (-c2.r)) + (c2 * c1.r);
        p = p * (1 / (c1.r - c2.r));
        std::vector<Point> ps = TangentPoint(c1, p);
        std::vector<Point> qs = TangentPoint(c2, p);
        const int N = std::min(ps.size(), qs.size());
        for (int i = 0; i < N; ++i)
            list.emplace_back(Line(ps[i], qs[i]));
    }

    // caluculate inner tangent
    if (equal(Distance(c1, c2), c1.r + c2.r)) {
        // two circle contact one point outernally | |$ $
        Point cross_point = CrossPoint(c1, c2)[0];
        Point up = (cross_point - c1).rotate90();
        list.emplace_back(Line(cross_point + up, cross_point - up));
    }
    else { // | |  $ $
        Point p = (c1 * c2.r) + (c2 * c1.r);
        p = p * (1 / (c1.r + c2.r));
        std::vector<Point> ps = TangentPoint(c1, p);
        std::vector<Point> qs = TangentPoint(c2, p);
        const int N = std::min(ps.size(), qs.size());
        for (int i = 0; i < N; ++i)
            list.emplace_back(Line(ps[i], qs[i]));
    }

    return list;
}


/**
 * Polygon
 */
class Polygon : public std::vector<Point> {
public:
    Polygon() {}
    Polygon(int size) : std::vector<Point>(size){}
    Polygon(std::initializer_list<Point> p) : std::vector<Point>(p) {}

    Number Area() const; // area of polygon : O(n)
    bool IsConvex() const; // Test whether it's convex polygon : O(n)
    std::vector<Point> ConvexHull() const; // Andrew's Monotone Chain Algorithm : O(n * log n)
    Polygon ConvexCut(const Line &l) const; // cut the polygon by line and return the left: O(n)

    // Is p contained or on segment or otherwise? : O(n)
    enum { OUT, ON, IN, };
    int Contain(const Point &p) const;
    // convex version : O(log n)
    int ConvexContain(const Point &p) const;

};

// Output of a polygon
std::ostream& operator<<(std::ostream &os, const Polygon &poly) {
    for (auto p : poly) os << p << ", ";
    return os;
}

Number Polygon::Area() const {
    const int n = (*this).size();
    assert(1 < n);

    Number area = abs_cross((*this)[n - 1], (*this)[0]);
    for (int i = 0; i < n - 1; ++i)
        area += abs_cross((*this)[i], (*this)[i + 1]);
    return 0.5 * area;
}

bool Polygon::IsConvex() const {
    // if given polygon is not simple polygon we should check for all (i-1, i, i+1)
    // (p[i].y <= p[i-1].y && p[i].y < p[i+1].y)
    // doesn't happen  without first index which y is the lowest
    const int n = (*this).size();
    CCW diff = OTHER;
    for (int i = 0; i < n; ++i) {
        CCW cur = ccw((*this)[i], (*this)[(i + 1) % n], (*this)[(i + 2) % n]);
        if (diff == OTHER && (cur == CLOCKWISE || cur == COUNTER_CLOCKWISE))
            diff = static_cast<CCW>(-cur);
        else if (cur == diff) return false;
    }
    return true;
}

int Polygon::Contain(const Point &p) const {
    const int n = (*this).size();
    bool count = false;
    for (int i = 0; i < n; ++i) {
        if (IsIntersect(Segment((*this)[i], (*this)[(i + 1) % n]), p))
            return ON;
        Point up = (*this)[i] - p, down = (*this)[(i + 1) % n] - p;
        if (up.y < down.y)
            std::swap(up, down);
        if (sign(down.y) <= 0 && sign(up.y) == 1 && sign(abs_cross(up, down)) == 1)
            count = !count;
    }
    return count ? IN : OUT;
}

int Polygon::ConvexContain(const Point &p) const {
    const int n = (*this).size();
    Point g = ((*this)[0] + (*this)[n / 3] + (*this)[2 * n / 3]) / 3.0; // inner point
    int a = 0, b = n;

    while (a + 1 < b) { // invariant : c is in fan g-poly[a]-poly[b]
        int c = (a + b) * 0.5;
        if (sign(abs_cross((*this)[a] - g, (*this)[c] - g)) == 1) { // angle < 180 deg
            if (sign(abs_cross((*this)[a] - g, p - g)) >= 0 &&
                sign(abs_cross((*this)[c] - g, p - g)) == -1)
                b = c;
            else
                a = c;
        }
        else {
            if (sign(abs_cross((*this)[a] - g, p - g)) == -1 &&
                sign(abs_cross((*this)[c] - g, p - g)) == 1)
                a = c;
            else
                b = c;
        }
    }

    // Assume that points in polygon are in the order of counter-clockwise
    b %= n;
    int res = sign(abs_cross((*this)[a] - p, (*this)[b] - p));
    return (res == -1 ? OUT : (res == 1 ? IN : ON));
}

// Andrew's Monotone Chain Algorithm : O(n * log n)
std::vector<Point> Polygon::ConvexHull() const {
    if ((*this).size() < 3) return (*this);

    Polygon poly = (*this);
    const int n = poly.size();
    int size = 0;
    std::vector<Point> chain(2 * n);

    std::sort(poly.begin(), poly.end());

    for (int i = 0; i < n; chain[size++] = poly[i++])  // lower hull
        while (size >= 2 && ccw(chain[size - 2], chain[size - 1], poly[i]) <= 0)
            --size;
    for (int i = n - 2, j = size + 1; 0 <= i; chain[size++] = poly[i--])  // upper hull
        while (size >= j && ccw(chain[size - 2], chain[size - 1], poly[i]) <= 0)
            --size;
    chain.resize(size - 1);
    return chain;
}

// rotating calipers algorithm : O(n)
Number ConvexDiameter(const std::vector<Point> &poly) {
    const int n = poly.size();

    std::pair<int, int> s; // first is min, second is max
    for (int i = 1; i < n; ++i) {
        if (poly[i].y < poly[s.first].y) s.first = i;
        if (poly[i].y > poly[s.second].y) s.second = i;
    }

    Number max_d = Distance(poly[s.first], poly[s.second]);
    std::pair<int, int> cur(s), max_p(s);

    // Assume that points in polygon are in the order of counter-clockwise
    do {
        Point v1 = poly[cur.second] - poly[(cur.second + 1) % n] + poly[cur.first];
        if (ccw(poly[cur.first], poly[(cur.first + 1) % n], v1) == COUNTER_CLOCKWISE)
            cur.first = (cur.first + 1) % n;
        else
            cur.second = (cur.second + 1) % n;

        Number cur_d = Distance(poly[cur.first], poly[cur.second]);
        if (max_d < cur_d) {
            max_p = cur;
            max_d = cur_d;
        }
    } while (cur != s);

    return max_d;
}

Polygon Polygon::ConvexCut(const Line &l) const {
    const int n = (*this).size();
    const Polygon &p = (*this);
    Polygon q; // left side polygon cutted by line

    for (int i = 0; i < n; ++i) {
        Point cur(p[i]), next(p[(i + 1) % n]);
        if (ccw(l, cur) != CLOCKWISE)
            q.emplace_back(cur);
        if (ccw(l, cur) * ccw(l, next) == -1)
            q.emplace_back(CrossPoint(l, Line(cur, next)));
    }

    return q;
}

int main() {
    std::cout << std::fixed << std::setprecision(10);
    std::cin.tie(0); std::ios::sync_with_stdio(false);

    int n, q;
    Line l;

    // Input
    std::cin >> n;
    Polygon g(n);
    for (int i = 0; i < n; ++i)
        std::cin >> g[i];
    std::cin >> q;
    while (q--) {
        std::cin >> l;
        auto poly = g.ConvexCut(l);
        if (poly.size() > 2)
            std::cout << poly.Area() << '\n';
        else
            std::cout << "0.0\n";
    }

    return 0;
}
