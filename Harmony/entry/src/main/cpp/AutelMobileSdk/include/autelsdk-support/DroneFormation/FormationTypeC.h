#ifndef FORMATIONTYPEC_H
#define FORMATIONTYPEC_H

#include <iostream>
#include "CommonDefines.h"
#include "PathSchedule.h"
#include "DroneFormation_global.h"

namespace DroneFormation {

class DRONEFORMATION_API DroneFormationC
{
public:
    // takeoff        - 飞机的当前位置（LLA）
    // num            - 飞机架数
    // target         - 目标位置
    // fmt            - C形编队参数
    // uav_pos        - 出参，得出的每一架飞机的位置
    void  ArrangeFmtLla(Point takeoff[], int num, Point &target, FormationTypeC &fmt, Point uav_pos[]);

    // a            - 出发点位置（LLA坐标）
    // b            - 到达点位置
    // num          - 出发和到达点数量
    // index        - 输出匹配的序列号，输出结果第i的出发点(a[i])，匹配第index[i]的到达点(b[index[i]])
    void JoinSortLla(Point a[], Point b[], int num, int index[]);
};

}; // AlgorithmLite

#endif
