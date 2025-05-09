#include <unistd.h>
#include <android/log.h>
#include <dlfcn.h>
#include <cstring>

#define LOG_TAG "ZygiskInjector"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define TARGET_PACKAGE "com.dts.freefireth"

const char *lib_path = "/data/adb/modules/zygisk_libsmooth/libs/arm64-v8a/libsmooth.so";

void inject_lib() {
    if (access(lib_path, F_OK) != 0) {
        LOGI("Library not found at path: %s", lib_path);
        return;
    }

    void *handle = dlopen(lib_path, RTLD_NOW);
    if (handle) {
        LOGI("libsmooth.so injected successfully.");
    } else {
        LOGI("Injection failed: %s", dlerror());
    }
}

extern "C" void zygisk_module_init() {
    LOGI("Zygisk module initialized");
}

extern "C" void zygisk_app_specialize(const char *pkg_name, uid_t uid, pid_t pid, uid_t gid,
                                     const char *se_info, const char *nice_name,
                                     bool is_child_zygote, bool is_zygote,
                                     const char *instruction_set, const char *app_data_dir) {
    if (pkg_name && strcmp(pkg_name, TARGET_PACKAGE) == 0) {
        LOGI("Target package matched: %s", pkg_name);
        inject_lib();
    }
}
