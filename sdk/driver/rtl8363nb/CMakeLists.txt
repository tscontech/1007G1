add_definitions(
    -DMDC_MDIO_OPERATION
)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/sdk/include/rtl8363nb/
)

ADD_LIBRARY(rtl8363nb STATIC
    acl.c
    cpu.c
    dot1x.c
    eee.c
    i2c.c
    igmp.c
    interrupt.c
    l2.c
    leaky.c
    led.c
    mirror.c
    oam.c
    port.c
    ptp.c
    qos.c
    rate.c
    rldp.c
    rtk_switch.c
    rtl8367c_asicdrv.c
    rtl8367c_asicdrv_acl.c
    rtl8367c_asicdrv_cputag.c
    rtl8367c_asicdrv_dot1x.c
    rtl8367c_asicdrv_eav.c
    rtl8367c_asicdrv_eee.c
    rtl8367c_asicdrv_fc.c
    rtl8367c_asicdrv_green.c
    rtl8367c_asicdrv_hsb.c
    rtl8367c_asicdrv_i2c.c
    rtl8367c_asicdrv_igmp.c
    rtl8367c_asicdrv_inbwctrl.c
    rtl8367c_asicdrv_interrupt.c
    rtl8367c_asicdrv_led.c
    rtl8367c_asicdrv_lut.c
    rtl8367c_asicdrv_meter.c
    rtl8367c_asicdrv_mib.c
    rtl8367c_asicdrv_mirror.c
    rtl8367c_asicdrv_misc.c
    rtl8367c_asicdrv_oam.c
    rtl8367c_asicdrv_phy.c
    rtl8367c_asicdrv_port.c
    rtl8367c_asicdrv_portIsolation.c
    rtl8367c_asicdrv_qos.c
    rtl8367c_asicdrv_rldp.c
    rtl8367c_asicdrv_rma.c
    rtl8367c_asicdrv_scheduling.c
    rtl8367c_asicdrv_storm.c
    rtl8367c_asicdrv_svlan.c
    rtl8367c_asicdrv_trunking.c
    rtl8367c_asicdrv_unknownMulticast.c
    rtl8367c_asicdrv_vlan.c
    smi.c
    stat.c
    storm.c
    svlan.c
    trap.c
    trunk.c
    vlan.c
)
