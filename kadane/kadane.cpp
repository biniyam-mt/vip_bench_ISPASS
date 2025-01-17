#include <iostream>
using namespace std;

#include "../config.h"
 
// Function to find the maximum sum of a contiguous subarray
// in a given integer array
VIP_ENCINT
kadane(VIP_ENCINT arr[], int n, VIP_ENCINT &ends_at)
{
  // stores the maximum sum subarray found so far
  VIP_ENCINT max_so_far = 0;
  ends_at = -1;
 
  // stores the maximum sum of subarray ending at the current position
  VIP_ENCINT max_ending_here = 0;
 
  // traverse the given array
  for (int i = 0; i < n; i++)
  {
    // update the maximum sum of subarray "ending" at index `i` (by adding the
    // current element to maximum sum ending at previous index `i-1`)
    max_ending_here = max_ending_here + arr[i];
 
    // if the maximum sum is negative, set it to 0 (which represents
    // an empty subarray)

/**** IISWC DO Transformation: IF Conversion - NA ****/
#ifdef VIP_DO_MODE
    VIP_ENCBOOL _pred = (max_ending_here > 0);
    max_ending_here = VIP_CMOV(_pred, max_ending_here, (VIP_ENCINT)0);
#else /* !VIP_DO_MODE */
    max_ending_here = max(max_ending_here, 0);
#endif /* !VIP_DO_MODE */


    // update the result if the current subarray sum is found to be greater

/**** IISWC DO Transformation: IF Conversion - NA ****/
#ifdef VIP_DO_MODE
    VIP_ENCBOOL _pred1 = (max_so_far < max_ending_here);
    ends_at = VIP_CMOV(_pred1, (VIP_ENCINT)i, ends_at);
    max_so_far = VIP_CMOV(_pred1, max_ending_here, max_so_far);
#else /* !VIP_DO_MODE */
    if (max_so_far < max_ending_here)
      ends_at = i;
    max_so_far = max(max_so_far, max_ending_here);
#endif /* !VIP_DO_MODE */
  }
  return max_so_far;
}
 
int
main()
{
  VIP_ENCINT arr[] = {
    8155, 17168, 11554, -14406, 13854, 20973, -26471, -11245, 25508, -24548, -2094, -16932, -23080,
    29777, -27647, -5927, 20197, -16505, -28944, 2518, 22405, 15304, -19199, 5439, 4971, 24179, 1119,
    16764, -24526, -973, -9585, 15066, 12069, -21990, -19708, -16603, 24065, 15869, -6208, 22922,
    2901, 24070, -16253, 15350, -27951, -817, -10363, -4185, -17835, -21493, -25281, -4842, -1425,
    6710, -7297, -17119, -10408, 18129, -28213, -12161, 13068, -4347, 27196, -9652, -19423, 6057,
    -22147, -10601, -17130, -13839, 4925, 27786, -9734, -25871, -2776, 16462, 13778, 11363, -6662,
    -24896, 19904, 29515, 9625, 18193, -17274, -3246, 27168, 508, -81, 15064, 19885, 18619, -5470,
    23422, -10780, -21517, 26606, -20833, -27943, -11223, -10137, -29356, 2701, -10774, 13286, -15863,
    24259, -3434, -16362, -4444, -20182, 7785, 23559, -16482, -23146, 7477, 25038, -19306, -26506,
    29314, 2174, 7862, -29266, -1236, -28187, 27877, -7969, 10314, -5142, 5466, 28920, 29191, -27061,
    27601, 7428, 12574, -5776, 27915, -13399, -11340, 3307, 7043, -6927, 16463, -6535, 26316, -10710,
    16103, -5578, 26102, -22493, 23027, 12203, 3251, 5281, -17123, -9919, 18986, -9330, -192, 16263,
    -19289, -22665, -2993, 27926, -3020, -10050, -4092, 17416, 26503, -16237, -25905, -19723, -5055,
    2901, 24070, -16253, 15350, -27951, -817, -10363, -4185, -17835, -21493, -25281, -4842, -1425,
    27601, 7428, 12574, -5776, 27915, -13399, -11340, 3307, 7043, -6927, 16463, -6535, 26316, -10710,
    29777, -27647, -5927, 20197, -16505, -28944, 2518, 22405, 15304, -19199, 5439, 4971, 24179, 1119,
    8155, 17168, 11554, -14406, 13854, 20973, -26471, -11245, 25508, -24548, -2094, -16932, -23080,
    -25496, -27164, -9845, 25985, 21965, 26979, -28295, -4574, -27464, -26163, 11498, -6302,
    29123, -4712, -24339, -27645, 23484, 12151, 14797, -5334, -15853, 9431, 7116, 27195, -1075,
    17134, 21955, -3745, -4717, 11285, -9264, -20400, 15249, -18604, 390, 25377, -7495,
    -24694, 25767, 17461, -21795, 1815, -5557, 22489, 11085, -6132, -2513, 131, 18955,
    -28518, -14482, 15781, 21178, 5485, -12187, -24004, 12344, 20129, -26045, -28136, -26435, 23729,
    -12384, 3157, 3121, -18724, -17193, 22853, -29225, 29921, -19534, -28048, -9185, -29704, -29260, -2534,
    21587, 4770, 4880, -9269, 9197, 25075, -3083, -4795, -28614, -8794, 20376, -12507, -14627, 8109,
    28004, -29128, -10195, 16767, -6852, -21305, 28599, -23297, -16460, 18601, 5359, -7017, -24250, -23556,
    16491, -23856, -16880, 19593, 6171, 12602, -29905, -27567, 18969, -12582, 18015, 7774, 23534, -26819,
    -8535, 13345, 9279, -20758, -1612, 13739, -29764, 6005, 2037, 14339, -23422, -11, -16605, -11701
  };
  int n = sizeof(arr)/sizeof(arr[0]);
  VIP_ENCINT max_sum, ends_at;
 
  fprintf(stdout, "Array size= %d\n", n);
  {
    Stopwatch s("VIP_Bench Runtime");
    max_sum = kadane(arr, n, ends_at);
  }
  fprintf(stdout, "The maximum sum of a contiguous subarray is %d (ending at index %d)\n", VIP_DEC(max_sum), VIP_DEC(ends_at));
  return 0;
}

