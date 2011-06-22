#ifndef COLOR_H#define COLOR_Hnamespace {	#define LTYPE float};class Color {
public:
	Color() : m_r(0), m_g(0), m_b(0) {}
	Color(float r, float g, float b) : m_r(r), m_g(g), m_b(b) {}
	LTYPE r() const;	LTYPE g() const;	LTYPE b() const;	void setR(LTYPE r);	void setG(LTYPE g);	void setB(LTYPE b);	float& operator[](unsigned int index);	Color& operator+=(const Color &color);	const Color operator+(const Color &color) const;protected:
	float m_r;
	float m_g;
	float m_b;
};/**
 * Get Methode fuer Rot-Komponente.
 * @return Rot-Komponente
 */
inline LTYPE Color::r() const
{
    return m_r;
}

/**
 * Get Methode fuer Gruen-Komponente.
 * @return Gruen-Komponente
 */
inline LTYPE Color::g() const
{
    return m_g;
}/**
 * Get Methode fuer Blau-Komponente.
 * @return Blau-Komponente
 */
inline LTYPE Color::b() const
{
    return m_b;
}/**
 * Set Methode fuer Rot-Komponente
 * @param r Neuer Wert fuer rot
 */
inline void Color::setR(LTYPE r)
{
    m_r = r;
}/**
 * Set Methode fuer Gruen-Komponente
 * @param r Neuer Wert fuer gruen
 */
inline void Color::setG(LTYPE g)
{
    m_g = g;
}/**
 * Set Methode fuer Blau-Komponente
 * @param r Neuer Wert fuer blau
 */
inline void Color::setB(LTYPE b)
{
    m_b = b;
}/**
 * Ueberladener Array Operator [] Read and Write.
 * Ermoeglicht Zugriff auf die Farbkomponenten R,G und B
 * [index=0]=R, [index=1]=G und [index=2]=B
 * Ist index > 2 wird stets der B zurueckgegeben.
 * @param index Index der Farbkomponente
 * @return Farbkomponente, dem Index entsprechend
 */
inline float& Color::operator[](unsigned int index)
{
	return index > 1 ?
			m_b : index == 1 ?
			m_g :
			m_r;
}

/**
 * Ueberladener += Operator
 * @param vector Rechtsseitiger Operand
 */
inline Color& Color::operator+=(const Color &color)
{
	m_r += color.m_r;
	m_g += color.m_g;
	m_b += color.m_b;

	return *this;
}

/**
 * Ueberladener + Operator
 * @param vector Rechtsseitiger Operand
 */
inline const Color Color::operator+(const Color &color) const
{
	return Color(*this) += color;
}#endif // COLOR_H