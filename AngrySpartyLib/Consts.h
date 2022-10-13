/**
 * @file Consts.h
 * @author Charles Owen
 *
 * Some basic handy constants
 */

#ifndef ANGRYSPARTY_CONSTS_H
#define ANGRYSPARTY_CONSTS_H

/**
 * Some basic handy constants
 */
class Consts {
public:
    /// Conversion of meters to centimeter display dimensions
    static constexpr double MtoCM = 100.0;

    /// Conversion of degrees to radians
    static constexpr double DtoR = 0.0174532925199;

    /// Convert of radians to degrees
    static constexpr double RtoD = 57.2957795131;
};

#endif //ANGRYSPARTY_CONSTS_H