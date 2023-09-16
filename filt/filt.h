/**
 * @file filt.h 
 * @author Key Liao
 * 
 */

#include <stdint.h>

#define i64 int64_t
#define u64 uint64_t
#define i32 int32_t
#define u32 uint32_t

/*=== BEGIN: Global Variables ===*/

typedef struct FilT_Param_T {
    u64 width;
    u64 nsamp;              // Number of samples in a simulation, and the number of simulation for a bin
    double p_low;           // Lower threshold of probability ofa single bin
    double p_xcut, p_ycut;  // Cut the highest fraction.
    char *in_tm_file;       // Input measurement results.
    char *in_tf_file;       // Input timing fluctuation samples.
    char *out_tr_file;      // Output real time estimation.
} filt_param_t;

typedef struct Prob_Bin_T {
    i64 t;
    double p;
} prob_bin_t;

typedef struct Prob_Hist_T {
    u64 nbin;
    prob_bin_t *pbin;
} prob_hist_t;

//extern int errno;

/*=== END: Global Variables ===*/

/*=== BEGIN: Interfaces ===*/

/**
 * Parsing input command-line arguments.
 * @param argc
 * @para argv
 */
// int arg_parse(int argc, char **argv);

/**
 * Slicing a rounded array to bins.
 * The min width is larger than args->rnd, the min probability is larger than args->p_low
 * @param arr Input array being sliced.
 * @param len The length of the input array.
 * @param p_low.
 * @param width.
 * @param phist A pointer to the histogram of sliced running times.
 */
int slice(i64 *arr, u64 len, double p_low, i64 width, prob_hist_t *phist);

/**
 * Reading csv file
 * @param fpath File path.
 * @param pcut The highest probability being cut.
 * @param len The length of returned array.
 * @param arr Data array.
 */
int read_csv(char *fpath, double pcut, u64 *len, i64 **arr);


/**
 * Performing filtering with FilT, enclosing subroutines
 * @param args FilT parameters.
 * @param tr_hist Pointer to the histogram of filtered running times.
 */
int run_filt(filt_param_t *args, prob_hist_t *tr_hist);

/**
 * Comparing function for qsort.
 */
int cmp(const void *a, const void *b);

/**
 * @brief 
 * @param tmh   Binned meausrement times.
 * @param tfh   Binned timing fluctuation samples.
 * @param trh   Binned real time estimations.
 * @param tf_arr    Sorted timing fluctuation raw array after cut.
 * @param tf_len    The length of tf_arr.
 * @param args      
 * @return int 
 */
int calc_tr(prob_hist_t *tmh, prob_hist_t *trh, i64 *tf_arr, u64 tf_len, filt_param_t *args);

/**
 * @brief 
 * @param tmh 
 * @param trh 
 * @param tf_arr 
 * @param tf_len 
 * @param psim 
 * @param args 
 * @return int 
 */
int sim_met(prob_hist_t *tmh, prob_hist_t *trh, i64 *tf_arr, u64 tf_len, double *psim, u64 nsamp);

/*=== END: Interfaces ===*/
