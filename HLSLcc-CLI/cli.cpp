#include <CLI/CLI.hpp>
#include <hlslcc/hlslcc.h>
#include <map>
#include <fstream>
#include <iostream>
#include <memory>

using std::string;

static const string hint_undocumented_flag = "Undocumented flag, see libHLSLcc source code";

int main(int argc, char** argv) {
    CLI::App app{"Command line interface for Unity's HLSLcc shader conversion tool"};
    argv = app.ensure_utf8(argv);

    string input_file;
    string output_file;

    app.add_option("input_file", input_file, "Input file path")
    ->required()
    ->check(CLI::ExistingFile);

    app.add_option("--output,-o", output_file, "Output file path, if omitted, result will be written to standard output");

    unsigned int flags = 0;
    app.add_flag_function("--uniform-buffer-object,!--no-uniform-buffer-object",
        [&](int count){flags = flags | HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT;},
        " HLSL constant buffers are treated as default-block unform arrays by default. This is done to support versions of GLSL which lack ARB_uniform_buffer_object functionality. Setting this flag causes each one to have its own uniform block."
    )->group("Compilation Flags");

    app.add_flag_function("--origin-upper-left,!--no-origin-upper-left",
        [&](int count) {flags = flags | HLSLCC_FLAG_ORIGIN_UPPER_LEFT;},
        hint_undocumented_flag
    )->group("Compilation Flags");

    

    app.add_flag_function("--pixel-center-integer,!--no-pixel-center-integer",
        [&](int count) {flags = flags | HLSLCC_FLAG_PIXEL_CENTER_INTEGER;},
        hint_undocumented_flag
    )->group("Compilation Flags");

    

    app.add_flag_function("--global-consts-never-in-ubo,!--no-global-consts-never-in-ubo",
        [&](int count) {flags = flags | HLSLCC_FLAG_GLOBAL_CONSTS_NEVER_IN_UBO;},
        hint_undocumented_flag
    )->group("Compilation Flags");

    

    app.add_flag_function("--gs-enabled,!--no-gs-enabled",
        [&](int count) {flags = flags | HLSLCC_FLAG_GS_ENABLED;},
        " GS enabled? Affects vertex shader (i.e. need to compile vertex shader again to use with/without GS). This flag is needed in order for the interfaces between stages to match when GS is in use. PS inputs VtxGeoOutput GS outputs VtxGeoOutput Vs outputs VtxOutput if GS enabled. VtxGeoOutput otherwise."
    )->group("Compilation Flags");

    

    app.add_flag_function("--tess-enabled,!--no-tess-enabled",
        [&](int count) {flags = flags | HLSLCC_FLAG_TESS_ENABLED;},
        hint_undocumented_flag
    )->group("Compilation Flags");

    

    app.add_flag_function("--dual-source-blending,!--no-dual-source-blending",
        [&](int count) {flags = flags | HLSLCC_FLAG_DUAL_SOURCE_BLENDING;},
        " Either use this flag or glBindFragDataLocationIndexed. When set the first pixel shader output is the first input to blend equation, the others go to the second input."
    )->group("Compilation Flags");

    

    app.add_flag_function("--inout-semantic-names,!--no-inout-semantic-names",
        [&](int count) {flags = flags | HLSLCC_FLAG_INOUT_SEMANTIC_NAMES;},
        " If set, shader inputs and outputs are declared with their semantic name."
    )->group("Compilation Flags");

    

    app.add_flag_function("--inout-append-semantic-names,!--no-inout-append-semantic-names",
        [&](int count) {flags = flags | HLSLCC_FLAG_INOUT_APPEND_SEMANTIC_NAMES;},
        " If set, shader inputs and outputs are declared with their semantic name appended."
    )->group("Compilation Flags");

    

    app.add_flag_function("--combine-texture-samplers,!--no-combine-texture-samplers",
        [&](int count) {flags = flags | HLSLCC_FLAG_COMBINE_TEXTURE_SAMPLERS;},
        " If set, combines texture/sampler pairs used together into samplers named \"texturename_X_samplername\"."
    )->group("Compilation Flags");

    

    app.add_flag_function("--disable-explicit-locations,!--no-disable-explicit-locations",
        [&](int count) {flags = flags | HLSLCC_FLAG_DISABLE_EXPLICIT_LOCATIONS;},
        " If set, attribute and uniform explicit location qualifiers are disabled (even if the language version supports that)"
    )->group("Compilation Flags");

    

    app.add_flag_function("--disable-globals-struct,!--no-disable-globals-struct",
        [&](int count) {flags = flags | HLSLCC_FLAG_DISABLE_GLOBALS_STRUCT;},
        " If set, global uniforms are not stored in a struct."
    )->group("Compilation Flags");

    

    app.add_flag_function("--sampler-precision-encoded-in-name,!--no-sampler-precision-encoded-in-name",
        [&](int count) {flags = flags | HLSLCC_FLAG_SAMPLER_PRECISION_ENCODED_IN_NAME;},
        " If set, treats sampler names ending with _highp, _mediump, and _lowp as sampler precision qualifiers Also removes that prefix from generated output"
    )->group("Compilation Flags");

    

    app.add_flag_function("--separable-shader-objects,!--no-separable-shader-objects",
        [&](int count) {flags = flags | HLSLCC_FLAG_SEPARABLE_SHADER_OBJECTS;},
        " If set, adds location qualifiers to intra-shader varyings."
    )->group("Compilation Flags");

    

    app.add_flag_function("--wrap-ubo,!--no-wrap-ubo",
        [&](int count) {flags = flags | HLSLCC_FLAG_WRAP_UBO;},
        " If set, wraps all uniform buffer declarations in a preprocessor macro #ifdef HLSLCC_ENABLE_UNIFORM_BUFFERS so that if that macro is undefined, all UBO declarations will become normal uniforms"
    )->group("Compilation Flags");

    

    app.add_flag_function("--remove-unused-globals,!--no-remove-unused-globals",
        [&](int count) {flags = flags | HLSLCC_FLAG_REMOVE_UNUSED_GLOBALS;},
        " If set, skips all members of the $Globals constant buffer struct that are not referenced in the shader code"
    )->group("Compilation Flags");

    

    app.add_flag_function("--translate-matrices,!--no-translate-matrices",
        [&](int count) {flags = flags | HLSLCC_FLAG_TRANSLATE_MATRICES;},
        " If set, translates all matrix declarations into vec4 arrays (as the DX bytecode treats them), and prefixes the name with 'hlslcc_mtx<rows>x<cols>'"
    )->group("Compilation Flags");

    

    app.add_flag_function("--vulkan-bindings,!--no-vulkan-bindings",
        [&](int count) {flags = flags | HLSLCC_FLAG_VULKAN_BINDINGS;},
        " If set, emits Vulkan-style (set, binding) bindings, also captures that info from any declaration named \"<Name>_hlslcc_set_X_bind_Y\" Unless bindings are given explicitly, they are allocated into set 0 (map stored in GLSLCrossDependencyData)"
    )->group("Compilation Flags");

    

    app.add_flag_function("--metal-shadow-sampler-linear,!--no-metal-shadow-sampler-linear",
        [&](int count) {flags = flags | HLSLCC_FLAG_METAL_SHADOW_SAMPLER_LINEAR;},
        " If set, metal output will use linear sampler for shadow compares, otherwise point sampler."
    )->group("Compilation Flags");

    

    app.add_flag_function("--avoid-shader-atomic-counters,!--no-avoid-shader-atomic-counters",
        [&](int count) {flags = flags | HLSLCC_FLAG_AVOID_SHADER_ATOMIC_COUNTERS;},
        " If set, avoid emit atomic counter (ARB_shader_atomic_counters) and use atomic functions provided by ARB_shader_storage_buffer_object instead."
    )->group("Compilation Flags");

    

    app.add_flag_function("--shader-framebuffer-fetch,!--no-shader-framebuffer-fetch",
        [&](int count) {flags = flags | HLSLCC_FLAG_SHADER_FRAMEBUFFER_FETCH;},
        " If set, this shader uses the GLSL extension EXT_shader_framebuffer_fetch"
    )->group("Compilation Flags");

    

    app.add_flag_function("--nvn-target,!--no-nvn-target",
        [&](int count) {flags = flags | HLSLCC_FLAG_NVN_TARGET;},
        " Build for Switch."
    )->group("Compilation Flags");

    

    app.add_flag_function("--uniform-buffer-object-with-instance-name,!--no-uniform-buffer-object-with-instance-name",
        [&](int count) {flags = flags | HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT_WITH_INSTANCE_NAME;},
        " If set, generate an instance name for constant buffers. GLSL specs 4.5 disallows uniform variables from different constant buffers sharing the same name as long as they are part of the same final linked program. Uniform buffer instance names solve this cross-shader symbol conflict issue."
    )->group("Compilation Flags");

    

    app.add_flag_function("--metal-tessellation,!--no-metal-tessellation",
        [&](int count) {flags = flags | HLSLCC_FLAG_METAL_TESSELLATION;},
        " Massage shader steps into Metal compute kernel from vertex/hull shaders + post-tessellation vertex shader from domain shader"
    )->group("Compilation Flags");

    

    app.add_flag_function("--disable-fastmath,!--no-disable-fastmath",
        [&](int count) {flags = flags | HLSLCC_FLAG_DISABLE_FASTMATH;},
        " Disable fastmath"
    )->group("Compilation Flags");

    

    app.add_flag_function("--force-explicit-locations,!--no-force-explicit-locations",
        [&](int count) {flags = flags | HLSLCC_FLAG_FORCE_EXPLICIT_LOCATIONS;},
        " If set, uniform explicit location qualifiers are enabled (even if the language version doesn't support that)"
    )->group("Compilation Flags");

    

    app.add_flag_function("--include-instructions-comments,!--no-include-instructions-comments",
        [&](int count) {flags = flags | HLSLCC_FLAG_INCLUDE_INSTRUCTIONS_COMMENTS;},
        " If set, each line of the generated source will be preceded by a comment specifying which DirectX bytecode instruction it maps to"
    )->group("Compilation Flags");

    

    app.add_flag_function("--keep-varying-locations,!--no-keep-varying-locations",
        [&](int count) {flags = flags | HLSLCC_FLAG_KEEP_VARYING_LOCATIONS;},
        " If set, try to generate consistent varying locations based on the semantic indices in the hlsl source, i.e \"TEXCOORD11\" gets assigned to layout(location = 11)"
    )->group("Compilation Flags");

    

    app.add_flag_function("--mobile-target,!--no-mobile-target",
        [&](int count) {flags = flags | HLSLCC_FLAG_MOBILE_TARGET;},
        " Code generation might vary for mobile targets, or using lower sampler precision than full by default"
    )->group("Compilation Flags");


    GLLang lang = LANG_DEFAULT;
    app.add_option("--lang,-l", lang, "Language target to generate for")
    ->transform(CLI::CheckedTransformer(std::map<string, GLLang>({
        {"default", LANG_DEFAULT},
        {"gl_es_100", LANG_ES_100},
        {"gl_es_first", LANG_ES_FIRST},
        {"gl_es_300", LANG_ES_300},
        {"gl_es_310", LANG_ES_310},
        {"gl_es_last", LANG_ES_LAST},
        {"gl_120", LANG_120},
        {"gl_first", LANG_GL_FIRST},
        {"gl_130", LANG_130},
        {"gl_140", LANG_140},
        {"gl_150", LANG_150},
        {"gl_330", LANG_330},
        {"gl_400", LANG_400},
        {"gl_410", LANG_410},
        {"gl_420", LANG_420},
        {"gl_430", LANG_430},
        {"gl_440", LANG_440},
        {"gl_last", LANG_GL_LAST},
        {"metal", LANG_METAL},
    }), CLI::ignore_case))
    ->group("Compilation Target");


    GlExtensions gl_ext = {0, 0, 0, 0, 0};

    app.add_flag_function("--gl-ext-arb-explicit-attrib-location,!--no-gl-ext-arb-explicit-attrib-location",
        [&](int count) {gl_ext.ARB_explicit_attrib_location = 1;},
        "Enable GL extension ARB_explicit_attrib_location for the compilation target"
    )->group("Compilation Target");
    app.add_flag_function("--gl-ext-arb-explicit-uniform-location,!--no-gl-ext-arb-explicit-uniform-location",
        [&](int count) {gl_ext.ARB_explicit_uniform_location = 1;},
        "Enable GL extension ARB_explicit_uniform_location for the compilation target"
    )->group("Compilation Target");
    app.add_flag_function("--gl-ext-arb-shading-language-420pack,!--no-gl-ext-arb-shading-language-420pack",
        [&](int count) {gl_ext.ARB_shading_language_420pack = 1;},
        "Enable GL extension ARB_shading_language_420pack for the compilation target"
    )->group("Compilation Target");
    app.add_flag_function("--gl-ext-ovr-multiview,!--no-gl-ext-ovr-multiview",
        [&](int count) {gl_ext.OVR_multiview = 1;},
        "Enable GL extension OVR_multiview for the compilation target"
    )->group("Compilation Target");
    app.add_flag_function("--gl-ext-ext-shader-framebuffer-fetch,!--no-gl-ext-ext-shader-framebuffer-fetch",
        [&](int count) {gl_ext.EXT_shader_framebuffer_fetch = 1;},
        "Enable GL extension EXT_shader_framebuffer_fetch for the compilation target"
    )->group("Compilation Target");

    //FIXME: support specifying shader dependencies via GLSLCrossDependencyData
    GLSLCrossDependencyData * dep_data = nullptr;

    CLI11_PARSE(app, argc, argv);

    //TODO: do something with returned sampler precision info
    HLSLccSamplerPrecisionInfo sampler_precision_info;
    //TODO: do something with reflection callbacks
    HLSLccReflection reflection_callbacks;

    GLSLShader result;

    std::ostream * output_stream;
    std::unique_ptr<std::ostream> managed_ostream = nullptr;
    if (output_file.empty()) {
        output_stream = &std::cout;
    } else {
        managed_ostream = std::make_unique<std::ofstream>(output_file);
        output_stream = managed_ostream.get();
    }

    int success = TranslateHLSLFromFile(
        input_file.c_str(),
        flags,
        lang,
        &gl_ext,
        dep_data,
        sampler_precision_info,
        reflection_callbacks,
        &result
    );

    if (success) {
        (*output_stream) << result.sourceCode;
    } else {
        std::cerr << "Error calling HLSLcc compiler";
        return 1;
    }

    return 0;
}