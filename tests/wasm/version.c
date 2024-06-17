#include "stdio.h"
#include "libc-wasm.h"

int main() {
    for(int i=-1; i<2; i++) {
        int major = LIBC_WASM_VERSION_MAJOR + i;

        if(major < 0) continue;
        for(int j=-1; j<2; j++) {
            int minor = LIBC_WASM_VERSION_MINOR + j;

            if(minor < 0) continue;
            for(int k=-1; k<2; k++) {
                int patch = LIBC_WASM_VERSION_PATCH + k;

                if(patch < 0) continue;
                printf("%d.%d.%d <  %d.%d.%d => %d\n", LIBC_WASM_VERSION_MAJOR, LIBC_WASM_VERSION_MINOR, LIBC_WASM_VERSION_PATCH, major, minor, patch, LIBC_WASM_VERSION_LT(major, minor, patch));
            }
        }
    }

    printf("\n");

    for(int i=-1; i<2; i++) {
        int major = LIBC_WASM_VERSION_MAJOR + i;

        if(major < 0) continue;

        for(int j=-1; j<2; j++) {
            int minor = LIBC_WASM_VERSION_MINOR + j;

            if(minor < 0) continue;

            for(int k=-1; k<2; k++) {
                int patch = LIBC_WASM_VERSION_PATCH + k;

                if(patch < 0) continue;
                printf("%d.%d.%d >  %d.%d.%d => %d\n", LIBC_WASM_VERSION_MAJOR, LIBC_WASM_VERSION_MINOR, LIBC_WASM_VERSION_PATCH, major, minor, patch, LIBC_WASM_VERSION_GT(major, minor, patch));
            }
        }
    }

    printf("\n");

    for(int i=-1; i<2; i++) {
        int major = LIBC_WASM_VERSION_MAJOR + i;

        if(major < 0) continue;
        for(int j=-1; j<2; j++) {
            int minor = LIBC_WASM_VERSION_MINOR + j;

            if(minor < 0) continue;
            for(int k=-1; k<2; k++) {
                int patch = LIBC_WASM_VERSION_PATCH + k;

                if(patch < 0) continue;
                printf("%d.%d.%d <= %d.%d.%d => %d\n", LIBC_WASM_VERSION_MAJOR, LIBC_WASM_VERSION_MINOR, LIBC_WASM_VERSION_PATCH, major, minor, patch, LIBC_WASM_VERSION_LE(major, minor, patch));
            }
        }
    }

    printf("\n");

    for(int i=-1; i<2; i++) {
        int major = LIBC_WASM_VERSION_MAJOR + i;

        if(major < 0) continue;
        for(int j=-1; j<2; j++) {
            int minor = LIBC_WASM_VERSION_MINOR + j;

            if(minor < 0) continue;
            for(int k=-1; k<2; k++) {
                int patch = LIBC_WASM_VERSION_PATCH + k;

                if(patch < 0) continue;
                printf("%d.%d.%d >= %d.%d.%d => %d\n", LIBC_WASM_VERSION_MAJOR, LIBC_WASM_VERSION_MINOR, LIBC_WASM_VERSION_PATCH, major, minor, patch, LIBC_WASM_VERSION_GE(major, minor, patch));
            }
        }
    }

    printf("\n");

    for(int i=-1; i<2; i++) {
        int major = LIBC_WASM_VERSION_MAJOR + i;

        if(major < 0) continue;
        for(int j=-1; j<2; j++) {
            int minor = LIBC_WASM_VERSION_MINOR + j;

            if(minor < 0) continue;
            for(int k=-1; k<2; k++) {
                int patch = LIBC_WASM_VERSION_PATCH + k;

                if(patch < 0) continue;
                printf("%d.%d.%d == %d.%d.%d => %d\n", LIBC_WASM_VERSION_MAJOR, LIBC_WASM_VERSION_MINOR, LIBC_WASM_VERSION_PATCH, major, minor, patch, LIBC_WASM_VERSION_EQ(major, minor, patch));
            }
        }
    }

    return 0;
}

