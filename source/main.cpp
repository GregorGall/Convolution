#include "LabSource.h"
#include "ConsoleGraph.h"

int main() {

	/* Параметры генератора */
	double carrier = 13e6;
	double period = 1 / carrier;
	double timePoint1 = 0;
	double timePoint2 = 21 * period;

	/* Немодулированый сигнал */
	LabSource plainSin(timePoint1, timePoint2, carrier);
	auto u1 = plainSin.sin().getValue();
	auto s1 = plainSin.convFFT().roll().getValue(Format::ABS);

	/* ЛЧМ */
	LabSource fmSin(timePoint1, timePoint2, carrier);
	fmSin.setModParameters({ linear, Modulation::FRQ, 2*carrier/timePoint2 });
	auto u2 = fmSin.sin().getValue();
	auto s2 = fmSin.convFFT().roll().getValue(Format::ABS);

	/* Фазовая модуляция кодом Баркера 7 */
	LabSource pmSin(timePoint1, timePoint2, carrier);
	auto barker7 = getCodeMod(timePoint2 / 7, { 1, 1, 1, 0, 0, 1, 0 });
	pmSin.setModParameters({ barker7, Modulation::PH, 0.5 });
	auto u3 = pmSin.sin().getValue();
	auto s3 = pmSin.convFFT().roll().getValue(Format::ABS);

	/* Отрисовка графиков */
	ConsoleGraph graph(750, 450, { 3, 2 });
	graph.plot(u1);
	graph.plot(s1, 1, 2);
	graph.plot(u2, 2, 1);
	graph.plot(s2, 2, 2);
	graph.plot(u3, 3, 1);
	graph.plot(s3, 3, 2);


	return 0;
}