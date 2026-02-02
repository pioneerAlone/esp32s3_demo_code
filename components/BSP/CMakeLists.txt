set(src_dirs 
            LED)
set(include_dirs 
            LED)

set(requires 
            driver
            led_strip 
            esp_driver_rmt
            )


idf_component_register(SRC_DIRS ${src_dirs}
                       INCLUDE_DIRS ${include_dirs}
                       REQUIRES ${requires}
                       )
#component_compile_options(-ffast-math -O3 -Wno-format)
target_compile_options(${COMPONENT_LIB} PRIVATE -ffast-math -O3 -Wno-format) 

# set(COMPONENT_SRCDIRS "LED")          # 源码目录
# set(COMPONENT_ADD_INCLUDEDIRS "LED")  # 头文件目录
# set(COMPONENT_REQUIRES "driver")      # 依赖的组件
