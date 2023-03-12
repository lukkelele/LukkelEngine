// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define LK_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif

#elif defined(__ANDROID__)
#define LK_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define LK_PLATFORM_LINUX
// #error "Linux is not supported (yet)!" // FIXME
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection
