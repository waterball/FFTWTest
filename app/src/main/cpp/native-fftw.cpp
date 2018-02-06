#include <jni.h>
#include <string>
#include <fftw3.h>
#include <sys/time.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_meicam_com_fftwtest_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    int size = 32;
    float *in = (float *)fftwf_malloc(size * size * sizeof(float));
    fftwf_complex *out = (fftwf_complex *)fftwf_malloc(size * (size+2) * sizeof(float));
    fftwf_plan p = fftwf_plan_dft_r2c_2d(size, size, in, out, FFTW_ESTIMATE);

    timeval begin, end;
    double elapse;
    gettimeofday(&begin, 0);
    for (int i = 0; i < 1000; ++i)
        fftwf_execute(p);
    gettimeofday(&end, 0);
    elapse = 1000.0 * (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000.0;
    elapse = elapse / 1000.0;

    char elapse_s[100];
    sprintf(elapse_s, "Elapse: %f ms\n", elapse);
    fftwf_destroy_plan(p);
    fftwf_free(in);
    fftwf_free(out);

    return env->NewStringUTF(elapse_s);

}
