#ifndef _START_H_
#define _START_H_

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _NOSTART_

extern int __main_void(void);
extern int main(int argc, char* argv[]) __attribute__((weak));

#endif /* _NOSTART_ */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _START_H_ */
