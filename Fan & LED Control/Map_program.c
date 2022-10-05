#include"STD_Types.h"
#include"Map_interface.h"

S32 MAP_Get_Input_Value(S32 Input_range_min,S32 Input_range_max,S32 Ouput_range_min,S32 Ouput_range_max,S32 Input_value){
	S32 y;
	y=((Ouput_range_max-Ouput_range_min)*(Input_value-Input_range_min))/(Input_range_max-Input_range_min)+Ouput_range_min;
	return y;
}
