SRC_URI = "file://${DL_DIR}/linux-samsung-e8.tar.gz"
S = "${WORKDIR}/${PN}"
B = "${S}"

# Get specific kernel version if there
def get_specific_revision(d):
    if d.getVar('SEL_SPECIFIC_REV_FLAG',True):
        return "${SEL_KERNEL_SPECIFIC_REV}"
    else:
        return "${AUTOREV}"
SRCREV = "${@get_specific_revision(d)}"

# Select KDEFCONFIG for virtualization
def get_kdefconfig(d):
    if d.getVar('SEL_SPECIFIC_REV_FLAG',True):
        return "${SEL_KERNEL_SPECIFIC_DEFCONFIG}"
    elif d.getVar('AUTOMOTIVE_VIRTUAL_PROJECT',True):
        return "exynos8890-virtualized_dom0_defconfig"
    else:
        return "defconfig"
KDEFCONFIG = "${@get_kdefconfig(d)}"

# Select DTB file for virtualization
def get_kernel_dtb_name(d):
    if d.getVar('SEL_SPECIFIC_REV_FLAG',True):
        return "${SEL_KERNEL_SPECIFIC_DT}"
    elif d.getVar('AUTOMOTIVE_VIRTUAL_PROJECT',True):
        return "exynos8890-virtualized_dom0.dtb"    
    else:  
        return "exynos8890-smdk8890.dtb"
KERNEL_DEVICETREE = "${@get_kernel_dtb_name(d)}"
		
# Mark archs/machines that this kernel supports
COMPATIBLE_MACHINE = "(automotive-samsung-e8)"
PV = "3.18.14+git"
#KDEFCONFIG ?= "defconfig"
KERNEL_CONFIG_COMMAND = "oe_runmake_call -C ${S} O=${B} ${KDEFCONFIG}"
PACKAGE_ARCH="${MACHINE_ARCH}"
