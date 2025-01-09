/******************************************************************************/
/*                                                                            */
/*                                    BANK0                                   */
/*                                                                            */
/******************************************************************************/

#define ERDPTL         0x00   // Read Pointer Low Byte
#define ERDPTL_Pos     (0U)     // Pozycja bitów dla ERDPTL
#define ERDPTL_Msk     (0xFF << ERDPTL_Pos)    // Maski dla wszystkich bitów w ERDPTL

#define ERDPTH         0x01   // Read Pointer High Byte
#define ERDPTH_Pos     (0U)     // Pozycja bitów dla ERDPTH (tylko bity 0-4 używane)
#define ERDPTH_Msk     (0x1F << ERDPTH_Pos)    // Maski dla bitów od 0 do 4 w ERDPTH (wskaźnik)

#define EWRPTL         0x02   // Write Pointer Low Byte
#define EWRPTL_Pos     (0U)     // Pozycja bitów dla EWRPTL
#define EWRPTL_Msk     (0xFF << EWRPTL_Pos)    // Maski dla wszystkich bitów w EWRPTL

#define EWRPTH         0x03   // Write Pointer High Byte
#define EWRPTH_Pos     (0U)     // Pozycja bitów dla EWRPTH (tylko bity 0-4 używane)
#define EWRPTH_Msk     (0x1F << EWRPTH_Pos)    // Maski dla bitów od 0 do 4 w EWRPTH

#define ETXSTL         0x04   // Transmit Buffer Start Low Byte
#define ETXSTL_Pos     (0U)     // Pozycja bitów dla ETXSTL
#define ETXSTL_Msk     (0xFF << ETXSTL_Pos)    // Maski dla wszystkich bitów w ETXSTL

#define ETXSTH         0x05   // Transmit Buffer Start High Byte
#define ETXSTH_Pos     (0U)     // Pozycja bitów dla ETXSTH
#define ETXSTH_Msk     (0x1F << ETXSTH_Pos)    // Maski dla wszystkich bitów w ETXSTH

#define ETXNDL         0x06   // Transmit Buffer End Low Byte
#define ETXNDL_Pos     (0U)     // Pozycja bitów dla ETXNDL
#define ETXNDL_Msk     (0xFF << ETXNDL_Pos)    // Maski dla wszystkich bitów w ETXNDL

#define ETXNDH         0x07   // Transmit Buffer End High Byte
#define ETXNDH_Pos     (0U)     // Pozycja bitów dla ETXNDH
#define ETXNDH_Msk     (0x1F << ETXNDH_Pos)    // Maski dla wszystkich bitów w ETXNDH

#define ERXSTL         0x08   // Receive Buffer Start Low Byte
#define ERXSTL_Pos     (0U)     // Pozycja bitów dla ERXSTL
#define ERXSTL_Msk     (0xFF << ERXSTL_Pos)    // Maski dla wszystkich bitów w ERXSTL

#define ERXSTH         0x09   // Receive Buffer Start High Byte
#define ERXSTH_Pos     (0U)     // Pozycja bitów dla ERXSTH
#define ERXSTH_Msk     (0x1F << ERXSTH_Pos)    // Maski dla wszystkich bitów w ERXSTH

#define ERXNDL         0x0A   // Receive Buffer End Low Byte
#define ERXNDL_Pos     (0U)     // Pozycja bitów dla ERXNDL
#define ERXNDL_Msk     (0xFF << ERXNDL_Pos)    // Maski dla wszystkich bitów w ERXNDL

#define ERXNDH         0x0B   // Receive Buffer End High Byte
#define ERXNDH_Pos     (0U)     // Pozycja bitów dla ERXNDH
#define ERXNDH_Msk     (0x1F << ERXNDH_Pos)    // Maski dla wszystkich bitów w ERXNDH

#define ERXRDPTL       0x0C   // Receive Buffer Read Pointer Low Byte
#define ERXRDPTL_Pos   (0U)     // Pozycja bitów dla ERXRDPTL
#define ERXRDPTL_Msk   (0xFF << ERXRDPTL_Pos)  // Maski dla wszystkich bitów w ERXRDPTL

#define ERXRDPTH       0x0D   // Receive Buffer Read Pointer High Byte
#define ERXRDPTH_Pos   (0U)     // Pozycja bitów dla ERXRDPTH (tylko bity 0-4 używane)
#define ERXRDPTH_Msk   (0x1F << ERXRDPTH_Pos)  // Maski dla bitów od 0 do 4 w ERXRDPTH (wskaźnik)

#define ERXWRPTL       0x0E   // Receive Buffer Write Pointer Low Byte
#define ERXWRPTL_Pos   (0U)     // Pozycja bitów dla ERXWRPTL
#define ERXWRPTL_Msk   (0xFF << ERXWRPTL_Pos)  // Maski dla wszystkich bitów w ERXWRPTL

#define ERXWRPTH       0x0F   // Receive Buffer Write Pointer High Byte
#define ERXWRPTH_Pos   (0U)     // Pozycja bitów dla ERXWRPTH (tylko bity 0-4 używane)
#define ERXWRPTH_Msk   (0x1F << ERXWRPTH_Pos)  // Maski dla bitów od 0 do 4 w ERXWRPTH (wskaźnik)

#define EDMASTL        0x10   // DMA Start Address Low Byte
#define EDMASTL_Pos    (0U)     // Pozycja bitów dla EDMASTL
#define EDMASTL_Msk    (0xFF << EDMASTL_Pos)   // Maski dla wszystkich bitów w EDMASTL

#define EDMASTH        0x11   // DMA Start Address High Byte
#define EDMASTH_Pos    (0U)     // Pozycja bitów dla EDMASTH
#define EDMASTH_Msk    (0x1F << EDMASTH_Pos)   // Maski dla wszystkich bitów w EDMASTH

#define EDMANDL        0x12   // DMA End Address Low Byte
#define EDMANDL_Pos    (0U)     // Pozycja bitów dla EDMANDL
#define EDMANDL_Msk    (0xFF << EDMANDL_Pos)   // Maski dla wszystkich bitów w EDMANDL

#define EDMANDH        0x13   // DMA End Address High Byte
#define EDMANDH_Pos    (0U)     // Pozycja bitów dla EDMANDH
#define EDMANDH_Msk    (0x1F << EDMANDH_Pos)   // Maski dla wszystkich bitów w EDMANDH

#define EDMADSTL       0x14   // DMA Destination Address Low Byte
#define EDMADSTL_Pos   (0U)     // Pozycja bitów dla EDMADSTL
#define EDMADSTL_Msk   (0xFF << EDMADSTL_Pos)  // Maski dla wszystkich bitów w EDMADSTL

#define EDMADSTH       0x15   // DMA Destination Address High Byte
#define EDMADSTH_Pos   (0U)     // Pozycja bitów dla EDMADSTH
#define EDMADSTH_Msk   (0x1F << EDMADSTH_Pos)  // Maski dla wszystkich bitów w EDMADSTH

#define EDMACSL        0x16   // DMA Checksum Low Byte
#define EDMACSL_Pos    (0U)     // Pozycja bitów dla EDMACSL
#define EDMACSL_Msk    (0xFF << EDMACSL_Pos)   // Maski dla wszystkich bitów w EDMACSL

#define EDMACSH        0x17   // DMA Checksum High Byte
#define EDMACSH_Pos    (0U)     // Pozycja bitów dla EDMACSH
#define EDMACSH_Msk    (0x1F << EDMACSH_Pos)   // Maski dla wszystkich bitów w EDMACSH


/******************************************************************************/
/*                                                                            */
/*                                    BANK1                                   */
/*                                                                            */
/******************************************************************************/

#define EHT0           0x00    // Hash Table Byte 0
#define EHT0_Pos       (0U)    
#define EHT0_Msk       (0xFF << EHT0_Pos)    // Hash Table Byte 0 Mask 

#define EHT1           0x01    // Hash Table Byte 1
#define EHT1_Pos       (0U)  
#define EHT1_Msk       (0xFF << EHT1_Pos)    // Hash Table Byte 1 Mask 

#define EHT2           0x02    // Hash Table Byte 2
#define EHT2_Pos       (0U) 
#define EHT2_Msk       (0xFF << EHT2_Pos)    // Hash Table Byte 2 Mask

#define EHT3           0x03    // Hash Table Byte 3
#define EHT3_Pos       (0U) 
#define EHT3_Msk       (0xFF << EHT3_Pos)    // Hash Table Byte 3 Mask

#define EHT4           0x04    // Hash Table Byte 4
#define EHT4_Pos       (0U) 
#define EHT4_Msk       (0xFF << EHT4_Pos)    // Hash Table Byte 4 Mask

#define EHT5           0x05    // Hash Table Byte 5
#define EHT5_Pos       (0U) 
#define EHT5_Msk       (0xFF << EHT5_Pos)    // Hash Table Byte 5 Mask

#define EHT6           0x06    // Hash Table Byte 6
#define EHT6_Pos       (0U) 
#define EHT6_Msk       (0xFF << EHT6_Pos)    // Hash Table Byte 6 Mask

#define EHT7           0x07    // Hash Table Byte 7
#define EHT7_Pos       (0U) 
#define EHT7_Msk       (0xFF << EHT7_Pos)    // Hash Table Byte 7 Mask

#define EPMM0          0x08    // Pattern Match Mask Byte 0
#define EPMM0_Pos      (0U) 
#define EPMM0_Msk      (0xFF << EPMM0_Pos)   // Pattern Match Mask Byte 0 Mask

#define EPMM1          0x09    // Pattern Match Mask Byte 1
#define EPMM1_Pos      (0U) 
#define EPMM1_Msk      (0xFF << EPMM1_Pos)   // Pattern Match Mask Byte 1 Mask

#define EPMM2          0x0A    // Pattern Match Mask Byte 2
#define EPMM2_Pos      (0U) 
#define EPMM2_Msk      (0xFF << EPMM2_Pos)   // Pattern Match Mask Byte 2 Mask

#define EPMM3          0x0B    // Pattern Match Mask Byte 3
#define EPMM3_Pos      (0U) 
#define EPMM3_Msk      (0xFF << EPMM3_Pos)   // Pattern Match Mask Byte 3 Mask

#define EPMM4          0x0C    // Pattern Match Mask Byte 4
#define EPMM4_Pos      (0U) 
#define EPMM4_Msk      (0xFF << EPMM4_Pos)   // Pattern Match Mask Byte 4 Mask

#define EPMM5          0x0D    // Pattern Match Mask Byte 5
#define EPMM5_Pos      (0U) 
#define EPMM5_Msk      (0xFF << EPMM5_Pos)   // Pattern Match Mask Byte 5 Mask

#define EPMM6          0x0E    // Pattern Match Mask Byte 6
#define EPMM6_Pos      (0U) 
#define EPMM6_Msk      (0xFF << EPMM6_Pos)   // Pattern Match Mask Byte 6 Mask

#define EPMM7          0x0F    // Pattern Match Mask Byte 7
#define EPMM7_Pos      (0U) 
#define EPMM7_Msk      (0xFF << EPMM7_Pos)   // Pattern Match Mask Byte 7 Mask

#define EPMCSL         0x10    // Pattern Match Checksum Low Byte
#define EPMCSL_Pos     (0U) 
#define EPMCSL_Msk     (0xFF << EPMCSL_Pos)  // Pattern Match Checksum Low Byte Mask

#define EPMCSH         0x11    // Pattern Match Checksum High Byte
#define EPMCSH_Pos     (0U) 
#define EPMCSH_Msk     (0xFF << EPMCSH_Pos)  // Pattern Match Checksum High Byte Mask

#define EPMOL          0x14    // Pattern Match Offset Low Byte
#define EPMOL_Pos      (0U) 
#define EPMOL_Msk      (0xFF << EPMOL_Pos)   // Pattern Match Offset Low Byte Mask

#define EPMOH          0x15    // Pattern Match Offset High Byte
#define EPMOH_Pos      (0U) 
#define EPMOH_Msk      (0x1F << EPMOH_Pos)   // Pattern Match Offset High Byte Mask

#define ERXFCON            0x18
#define ERXFCON_BCEN_Pos   (0U)
#define ERXFCON_BCEN_Msk   (0x01 << ERXFCON_BCEN_Pos)
#define ERXFCON_MCEN_Pos   (1U)
#define ERXFCON_MCEN_Msk   (0x01 << ERXFCON_MCEN_Pos)
#define ERXFCON_HTEN_Pos   (2U)
#define ERXFCON_HTEN_Msk   (0x01 << ERXFCON_HTEN_Pos)
#define ERXFCON_MPEN_Pos   (3U)
#define ERXFCON_MPEN_Msk   (0x01 << ERXFCON_MPEN_Pos)
#define ERXFCON_PMEN_Pos   (4U)
#define ERXFCON_PMEN_Msk   (0x01 << ERXFCON_PMEN_Pos)
#define ERXFCON_CRCEN_Pos  (5U)
#define ERXFCON_CRCEN_Msk  (0x01 << ERXFCON_CRCEN_Pos)
#define ERXFCON_ANDOR_Pos  (6U)
#define ERXFCON_ANDOR_Msk  (0x01 << ERXFCON_ANDOR_Pos)
#define ERXFCON_UCEN_Pos   (7U)
#define ERXFCON_UCEN_Msk   (0x01 << ERXFCON_UCEN_Pos)

#define EPKTCNT            0x19


/******************************************************************************/
/*                                                                            */
/*                                    BANK2                                   */
/*                                                                            */
/******************************************************************************/
#define MACON1               0x00    // MAC Control Register 1
#define MACON1_TXPAUS_Pos    (3U)    // Transmit Pause Control bit position
#define MACON1_TXPAUS_Msk    (0x01 << MACON1_TXPAUS_Pos)   // Transmit Pause Control mask
#define MACON1_RXPAUS_Pos    (2U)   // Receive Pause Control bit position
#define MACON1_RXPAUS_Msk    (0x01 << MACON1_RXPAUS_Pos)   // Receive Pause Control mask
#define MACON1_PASSALL_Pos   (1U)    // MAC Receive Enable bit position
#define MACON1_PASSALL_Msk   (0x01 << MACON1_PASSALL_Pos)   // MAC Receive Enable mask
#define MACON1_MARXEN_Pos    (0U)    // MAC On/Off bit position
#define MACON1_MARXEN_Msk   (0x01 << MACON1_MARXEN_Pos)    // MAC On/Off mask

#define MACON3               0x02    // MAC Control Register 3
#define MACON3_PADCFG2_Pos   (7U)    // Padding Configuration 2 bit position
#define MACON3_PADCFG2_Msk   (0x01 << MACON3_PADCFG2_Pos)  // Padding Configuration 2 mask
#define MACON3_PADCFG1_Pos   (6U)    // Padding Configuration 1 bit position
#define MACON3_PADCFG1_Msk   (0x01 << MACON3_PADCFG1_Pos)  // Padding Configuration 1 mask
#define MACON3_PADCFG0_Pos   (5U)    // Padding Configuration 0 bit position
#define MACON3_PADCFG0_Msk   (0x01 << MACON3_PADCFG0_Pos)  // Padding Configuration 0 mask
#define MACON3_TXCRCEN_Pos   (4U)    // Transmit CRC Enable bit position
#define MACON3_TXCRCEN_Msk   (0x01 << MACON3_TXCRCEN_Pos)  // Transmit CRC Enable mask
#define MACON3_PHDREN_Pos    (3U)    // PHY Deferral Enable bit position
#define MACON3_PHDREN_Msk    (0x01 << MACON3_PHDREN_Pos)   // PHY Deferral Enable mask
#define MACON3_HFRMEN_Pos    (2U)    // High-Speed Mode Enable bit position
#define MACON3_HFRMEN_Msk    (0x01 << MACON3_HFRMEN_Pos)   // High-Speed Mode Enable mask
#define MACON3_FRMLNEN_Pos   (1U)    // Frame Length Enable bit position
#define MACON3_FRMLNEN_Msk   (0x01 << MACON3_FRMLNEN_Pos)  // Frame Length Enable mask
#define MACON3_FULDPX_Pos    (0U)    // Full-Duplex Enable bit position
#define MACON3_FULDPX_Msk    (0x01 << MACON3_FULDPX_Pos)   // Full-Duplex Enable mask

#define MACON4             0x03    // MAC Control Register 4
#define MACON4_DEFER_Pos   (7U)    // Deferred Transmit Enable bit position
#define MACON4_DEFER_Msk   (0x01 << MACON4_DEFER_Pos)  // Deferred Transmit Enable mask
#define MACON4_BPBEN_Pos   (6U)    // Backpressure Enable bit position
#define MACON4_BPBEN_Msk   (0x01 << MACON4_BPBEN_Pos)  // Backpressure Enable mask
#define MACON4_NOBKOFF_Pos (5U)    // No Backpressure On-off Control bit position
#define MACON4_NOBKOFF_Msk (0x01 << MACON4_NOBKOFF_Pos) // No Backpressure On-off Control mask

#define MABBIPG          0x04    // Back-to-Back Inter-Packet Gap
#define MABBIPG_Pos      (0U)    // Back-to-back packet gap control bit position
#define MABBIPG_Msk      (0x7F << MABBIPG_Pos)     // Back-to-back packet gap mask

#define MAIPGL           0x06    // Non-Back-to-Back Inter-Packet Gap Low Byte
#define MAIPGL_Pos      (0U)    // Non-back-to-back inter-packet gap Low Byte position
#define MAIPGL_Msk      (0x7F << MAIPGL_Pos)     // Non-back-to-back Inter-Packet Gap Low Byte mask

#define MAIPGH           0x07    // Non-Back-to-Back Inter-Packet Gap High Byte
#define MAIPGH_Pos      (0U)    // Non-back-to-back inter-packet gap High Byte position
#define MAIPGH_Msk      (0x7F << MAIPGH_Pos)     // Non-back-to-back Inter-Packet Gap High Byte mask

#define MACLCON1         0x08    // Retransmission Maximum
#define MACLCON1_Pos     (5U)   // Delay collision enable control bit position
#define MACLCON1_Msk     (0x1F << MACLCON1_Pos)    // Delay Collision Check Enable mask

#define MACLCON2         0x09    // Collision Window
#define MACLCON2_Pos     (4U)    // Transmit Collision Bit Value control bit position
#define MACLCON2_Msk     (0x3F << MACLCON2_Pos)    // Transmit Collision Value control mask


#define MAMXFLL          0x0A    // Maximum Frame Length Low Byte
#define MAMXFLL_Pos      (0U)    // Max Frame Length Low Byte position
#define MAMXFLL_Msk      (0xFF << MAMXFLL_Pos)   // Max Frame Length Low Byte mask


#define MAMXFLH          0x0B    // Maximum Frame Length High Byte
#define MAMXFLH_Pos      (0U)    // Max Frame Length High Byte position
#define MAMXFLH_Msk      (0xFF << MAMXFLH_Pos)   // Max Frame Length High Byte mask

#define MICMD              0x12    // MII Command Register
#define MICMD_MIISCAN_Pos  (1U)   // MII Scan bit position
#define MICMD_MIISCAN_Msk  (0x01 << MICMD_MIISCAN_Pos)  // MII Scan mask
#define MICMD_MIIRD_Pos    (0U)   // MII Read bit position
#define MICMD_MIIRD_Msk    (0x01 << MICMD_MIIRD_Pos)    // MII Read mask


#define MIREGADR      0x14    // MII Register Address
#define MIREGADR_Pos  (0U)    // MII Register Address position
#define MIREGADR_Msk  (0x1F << MIREGADR_Pos) // MII Register Address mask

#define MIWRL         0x16    // MII Write Data Low Byte
#define MIWRL_Pos     (0U)    // Write Data Low Byte position
#define MIWRL_Msk     (0xFF << MIWRL_Pos)    // Write Data Low Byte mask

#define MIWRH         0x17    // MII Write Data High Byte
#define MIWRH_Pos     (0U)    // Write Data High Byte position
#define MIWRH_Msk     (0xFF << MIWRH_Pos)    // Write Data High Byte mask

#define MIRDL         0x18    // MII Read Data Low Byte
#define MIRDL_Pos     (0U)    // Read Data Low Byte position
#define MIRDL_Msk     (0xFF << MIRDL_Pos)    // Read Data Low Byte mask

#define MIRDH         0x19    // MII Read Data High Byte
#define MIRDH_Pos     (0U)    // Read Data High Byte position
#define MIRDH_Msk     (0xFF << MIRDH_Pos)    // Read Data High Byte mask


/******************************************************************************/
/*                                                                            */
/*                                    BANK3                                   */
/*                                                                            */
/******************************************************************************/
#define MAADR5         0x00    // MAC Address Byte 5
#define MAADR5_Pos     (0U)     // MAC Address Byte 5 position
#define MAADR5_Msk     (0xFF << MAADR5_Pos)    // MAC Address Byte 5 mask

#define MAADR6         0x01    // MAC Address Byte 6
#define MAADR6_Pos     (0U)     // MAC Address Byte 6 position
#define MAADR6_Msk     (0xFF << MAADR6_Pos)    // MAC Address Byte 6 mask

#define MAADR3         0x02    // MAC Address Byte 3
#define MAADR3_Pos     (0U)     // MAC Address Byte 3 position
#define MAADR3_Msk     (0xFF << MAADR3_Pos)    // MAC Address Byte 3 mask

#define MAADR4         0x03    // MAC Address Byte 4
#define MAADR4_Pos     (0U)     // MAC Address Byte 4 position
#define MAADR4_Msk     (0xFF << MAADR4_Pos)    // MAC Address Byte 4 mask

#define MAADR1         0x04    // MAC Address Byte 1
#define MAADR1_Pos     (0U)     // MAC Address Byte 1 position
#define MAADR1_Msk     (0xFF << MAADR1_Pos)    // MAC Address Byte 1 mask

#define MAADR2         0x05    // MAC Address Byte 2
#define MAADR2_Pos     (0U)     // MAC Address Byte 2 position
#define MAADR2_Msk     (0xFF << MAADR2_Pos)    // MAC Address Byte 2 mask

#define EBSTSD         0x06    // Built-in Self-Test Fill Seed
#define EBSTSD_Pos     (0U)     // Built-in Self-Test Fill Seed position
#define EBSTSD_Msk     (0xFF << EBSTSD_Pos)    // Built-in Self-Test Fill Seed mask

#define EBSTCON             0x07    // Built-in Self-Test Control
#define EBSTCON_PSV2_Pos    (7U)      // PSV2 position in EBSTCON
#define EBSTCON_PSV2_Msk    (0x01 << EBSTCON_PSV2_Pos)    // PSV2 mask in EBSTCON
#define EBSTCON_PSV1_Pos    (6U)      // PSV1 position in EBSTCON
#define EBSTCON_PSV1_Msk    (0x01 << EBSTCON_PSV1_Pos)    // PSV1 mask in EBSTCON
#define EBSTCON_PSV0_Pos    (5U)      // PSV0 position in EBSTCON
#define EBSTCON_PSV0_Msk    (0x01 << EBSTCON_PSV0_Pos)    // PSV0 mask in EBSTCON
#define EBSTCON_PSEL_Pos    (4U)      // PSEL position in EBSTCON
#define EBSTCON_PSEL_Msk    (0x01 << EBSTCON_PSEL_Pos)    // PSEL mask in EBSTCON
#define EBSTCON_TMSEL1_Pos  (3U)      // TMSEL1 position in EBSTCON
#define EBSTCON_TMSEL1_Msk  (0x01 << EBSTCON_TMSEL1_Pos)  // TMSEL1 mask in EBSTCON
#define EBSTCON_TMSEL0_Pos  (2U)      // TMSEL0 position in EBSTCON
#define EBSTCON_TMSEL0_Msk  (0x01 << EBSTCON_TMSEL0_Pos)  // TMSEL0 mask in EBSTCON
#define EBSTCON_TME_Pos     (1U)      // TME position in EBSTCON
#define EBSTCON_TME_Msk     (0x01 << EBSTCON_TME_Pos)     // TME mask in EBSTCON
#define EBSTCON_BISTST_Pos  (0U)      // BISTST position in EBSTCON
#define EBSTCON_BISTST_Msk  (0x01 << EBSTCON_BISTST_Pos)  // BISTST mask in EBSTCON

#define EBSTCSL        0x08    // Built-in Self-Test Checksum Low Byte
#define EBSTCSL_Pos    (0U)     // Built-in Self-Test Checksum Low Byte position
#define EBSTCSL_Msk    (0xFF << EBSTCSL_Pos)   // Built-in Self-Test Checksum Low Byte mask

#define EBSTCSH        0x09    // Built-in Self-Test Checksum High Byte
#define EBSTCSH_Pos    (0U)     // Built-in Self-Test Checksum High Byte position
#define EBSTCSH_Msk    (0xFF << EBSTCSH_Pos)   // Built-in Self-Test Checksum High Byte mask

#define MISTAT               0x0A    // MII Status Register
#define MISTAT_NVALID_Pos    (2U)      // NVALID position in MISTAT
#define MISTAT_NVALID_Msk    (0x01 << MISTAT_NVALID_Pos)    // NVALID mask in MISTAT
#define MISTAT_SCAN_Pos      (1U)      // SCAN position in MISTAT
#define MISTAT_SCAN_Msk      (0x01 << MISTAT_SCAN_Pos)      // SCAN mask in MISTAT
#define MISTAT_BUSY_Pos      (0U)      // BUSY position in MISTAT
#define MISTAT_BUSY_Msk      (0x01 << MISTAT_BUSY_Pos)      // BUSY mask in MISTAT

#define EREVID         0x12    // Ethernet Revision ID
#define EREVID_Pos     (0U)     // Ethernet Revision ID position
#define EREVID_Msk     (0x1F << EREVID_Pos)    // Ethernet Revision ID mask

#define ECOCON             0x15    // Clock Output Control
#define ECOCON_COCON2_Pos  (2U)     // COCON2 position in ECOCON
#define ECOCON_COCON2_Msk  (0x01 << ECOCON_COCON2_Pos)    // COCON2 mask in ECOCON
#define ECOCON_COCON1_Pos  (1U)     // COCON1 position in ECOCON
#define ECOCON_COCON1_Msk  (0x01 << ECOCON_COCON1_Pos)    // COCON1 mask in ECOCON
#define ECOCON_COCON0_Pos  (0U)     // COCON0 position in ECOCON
#define ECOCON_COCON0_Msk  (0x01 << ECOCON_COCON0_Pos)    // COCON0 mask in ECOCON

#define EFLOCON              0x17    // Ethernet Flow Control
#define EFLOCON_FULDPXS_Pos  (2U)   // FULDPXS position in EFLOCON
#define EFLOCON_FULDPXS_Msk  (0x01 << EFLOCON_FULDPXS_Pos)    // FULDPXS mask in EFLOCON
#define EFLOCON_FCEN1_Pos    (1U)   // FCEN1 position in EFLOCON
#define EFLOCON_FCEN1_Msk    (0x01 << EFLOCON_FCEN1_Pos)     // FCEN1 mask in EFLOCON
#define EFLOCON_FCEN0_Pos    (0U)   // FCEN0 position in EFLOCON
#define EFLOCON_FCEN0_Msk    (0x01 << EFLOCON_FCEN0_Pos)     // FCEN0 mask in EFLOCON

#define EPAUSL           0x18    // Pause Timer Value Low Byte
#define EPAUSL_Pos       (0U)     // Pause Timer Value Low Byte position
#define EPAUSL_Msk       (0xFF << EPAUSL_Pos)    // Pause Timer Value Low Byte mask

#define EPAUSH           0x19    // Pause Timer Value High Byte
#define EPAUSH_Pos       (0U)     // Pause Timer Value High Byte position
#define EPAUSH_Msk       (0xFF << EPAUSH_Pos)    // Pause Timer Value High Byte mask


/******************************************************************************/
/*                                                                            */
/*                             COMMON REGISTERS                               */
/*                                                                            */
/******************************************************************************/
#define EIE              0x1B    // Ethernet Interrupt Enable
#define EIE_INTIE_Pos    (7U)     // Interrupt Enable bit in EIE
#define EIE_INTIE_Msk    (0x01 << EIE_INTIE_Pos)    // Interrupt Enable mask
#define EIE_PKTIE_Pos    (6U)     // Packet Interrupt Enable bit in EIE
#define EIE_PKTIE_Msk    (0x01 << EIE_PKTIE_Pos)    // Packet Interrupt Enable mask
#define EIE_DMAIE_Pos    (5U)     // DMA Interrupt Enable bit in EIE
#define EIE_DMAIE_Msk    (0x01 << EIE_DMAIE_Pos)    // DMA Interrupt Enable mask
#define EIE_LINKIE_Pos   (4U)     // Link Status Interrupt Enable bit in EIE
#define EIE_LINKIE_Msk   (0x01 << EIE_LINKIE_Pos)   // Link Status Interrupt Enable mask
#define EIE_TXIE_Pos     (3U)     // Transmit Interrupt Enable bit in EIE
#define EIE_TXIE_Msk     (0x01 << EIE_TXIE_Pos)    // Transmit Interrupt Enable mask
#define EIE_TXERIE_Pos   (1U)     // Transmit Error Interrupt Enable bit in EIE
#define EIE_TXERIE_Msk   (0x01 << EIE_TXERIE_Pos)   // Transmit Error Interrupt Enable mask
#define EIE_RXERIE_Pos   (0U)     // Receive Error Interrupt Enable bit in EIE
#define EIE_RXERIE_Msk   (0x01 << EIE_RXERIE_Pos)   // Receive Error Interrupt Enable mask

#define EIR              0x1C    // Ethernet Interrupt Request
#define EIR_PKTIF_Pos    (6U)     // Packet Interrupt Flag bit in EIR
#define EIR_PKTIF_Msk    (0x01 << EIR_PKTIF_Pos)    // Packet Interrupt Flag mask
#define EIR_DMAIF_Pos    (5U)     // DMA Interrupt Flag bit in EIR
#define EIR_DMAIF_Msk    (0x01 << EIR_DMAIF_Pos)    // DMA Interrupt Flag mask
#define EIR_LINKIF_Pos   (4U)     // Link Status Interrupt Flag bit in EIR
#define EIR_LINKIF_Msk   (0x01 << EIR_LINKIF_Pos)   // Link Status Interrupt Flag mask
#define EIR_TXIF_Pos     (3U)     // Transmit Interrupt Flag bit in EIR
#define EIR_TXIF_Msk     (0x01 << EIR_TXIF_Pos)    // Transmit Interrupt Flag mask
#define EIR_TXERIF_Pos   (1U)     // Transmit Interrupt Flag bit in EIR
#define EIR_TXERIF_Msk   (0x01 << EIR_TXIF_Pos)    // Transmit Interrupt Flag mask
#define EIR_RXERIF_Pos   (0U)     // Transmit Interrupt Flag bit in EIR
#define EIR_RXERIF_Msk   (0x01 << EIR_TXIF_Pos)    // Transmit Interrupt Flag mask

#define ESTAT           0x1D    // Ethernet Status
#define ESTAT_INT_Pos     (7U)   // Interrupt Indicator bit in ESTAT
#define ESTAT_INT_Msk     (0x01 << ESTAT_INT_Pos)   // Interrupt Indicator mask
#define ESTAT_BUFER_Pos   (6U)   // Buffer Error bit in ESTAT
#define ESTAT_BUFER_Msk   (0x01 << ESTAT_BUFER_Pos)   // Buffer Error mask
#define ESTAT_LATECOL_Pos (4U)  // Late Collision Detection bit in ESTAT
#define ESTAT_LATECOL_Msk (0x01 << ESTAT_LATECOL_Pos) // Late Collision mask
#define ESTAT_RXBUSY_Pos  (2U)    // Receiver Busy Flag bit in ESTAT
#define ESTAT_RXBUSY_Msk  (0x01 << ESTAT_RXBUSY_Pos) // Receiver Busy Flag mask
#define ESTAT_TXABRT_Pos  (1U)    // Transmit Abort bit in ESTAT
#define ESTAT_TXABRT_Msk  (0x01 << ESTAT_TXABRT_Pos)   // Transmit Abort mask
#define ESTAT_CLKRDY_Pos  (0U)    // Clock Ready bit in ESTAT
#define ESTAT_CLKRDY_Msk  (0x01 << ESTAT_CLKRDY_Pos)   // Clock Ready mask

#define ECON2             0x1E    // Ethernet Control 2
#define ECON2_AUTOINC_Pos (7U)   // Auto Increment bit in ECON2
#define ECON2_AUTOINC_Msk (0x01 << ECON2_AUTOINC_Pos)   // Auto Increment mask
#define ECON2_PKTDEC_Pos  (6U)    // Packet Decrement bit in ECON2
#define ECON2_PKTDEC_Msk  (0x01 << ECON2_PKTDEC_Pos)     // Packet Decrement mask
#define ECON2_PWRSV_Pos   (5U)    // Power Save bit in ECON2
#define ECON2_PWRSV_Msk   (0x01 << ECON2_PWRSV_Pos)   // Power Save mask
#define ECON2_VRPS_Pos    (3U)    // Voltage Regulator Power Save bit in ECON2
#define ECON2_VRPS_Msk    (0x01 << ECON2_VRPS_Pos)    // Voltage Regulator Power Save mask

#define ECON1             0x1F    // Ethernet Control 1
#define ECON1_TXRST_Pos   (7U)    // Transmit Reset bit in ECON1
#define ECON1_TXRST_Msk   (0x01 << ECON1_TXRST_Pos)   // Transmit Reset mask
#define ECON1_RXRST_Pos   (6U)    // Receive Reset bit in ECON1
#define ECON1_RXRST_Msk   (0x01 << ECON1_RXRST_Pos)   // Receive Reset mask
#define ECON1_DMAST_Pos   (5U)    // DMA Start bit in ECON1
#define ECON1_DMAST_Msk   (0x01 << ECON1_DMAST_Pos)   // DMA Start mask
#define ECON1_CSUMEN_Pos  (4U)    // Checksum Enable bit in ECON1
#define ECON1_CSUMEN_Msk  (0x01 << ECON1_CSUMEN_Pos)  // Checksum Enable mask
#define ECON1_TXRTS_Pos   (3U)    // Transmit Request to Send bit in ECON1
#define ECON1_TXRTS_Msk   (0x01 << ECON1_TXRTS_Pos)   // Transmit Request to Send mask
#define ECON1_RXEN_Pos    (2U)    // Receive Enable bit in ECON1
#define ECON1_RXEN_Msk    (0x01 << ECON1_RXEN_Pos)    // Receive Enable mask
#define ECON1_BSEL_Pos    (0U)    // Bank Select in ECON1
#define ECON1_BSEL_Msk    (0x03 << ECON1_BSEL_Pos)   // Bank Select bit 1 mask

/******************************************************************************/
/*                                                                            */
/*                              PHY REGISTERS                                 */
/*                                                                            */
/******************************************************************************/
#define PHCON1         0x00    // PHY Control Register 1
#define PHCON1_PRST_Pos       (15U)    // PHY Reset
#define PHCON1_PRST_Msk       (0x01 << PHCON1_PRST_Pos)
#define PHCON1_PLOOPBK_Pos    (14U)    // PHY Loopback
#define PHCON1_PLOOPBK_Msk    (0x01 << PHCON1_PLOOPBK_Pos)
#define PHCON1_PPWRSV_Pos     (11U)    // PHY Power Saving
#define PHCON1_PPWRSV_Msk     (0x01 << PHCON1_PPWRSV_Pos)
#define PHCON1_PDPXMD_Pos     (8U)     // PHY Duplex Mode
#define PHCON1_PDPXMD_Msk     (0x01 << PHCON1_PDPXMD_Pos)

#define PHSTAT1        0x01    // PHY Status Register 1
#define PHSTAT1_PFDPX_Pos    (12U)    // Full Duplex
#define PHSTAT1_PFDPX_Msk    (0x01 << PHSTAT1_PFDPX_Pos)
#define PHSTAT1_PHDPX_Pos    (11U)    // Duplex Mode
#define PHSTAT1_PHDPX_Msk    (0x01 << PHSTAT1_PHDPX_Pos)
#define PHSTAT1_LLSTAT_Pos   (2U)     // Link Status
#define PHSTAT1_LLSTAT_Msk   (0x01 << PHSTAT1_LLSTAT_Pos)
#define PHSTAT1_JBSTAT_Pos   (1U)     // Jabber Status
#define PHSTAT1_JBSTAT_Msk   (0x01 << PHSTAT1_JBSTAT_Pos)

#define PHID1          0x02    // PHY Identifier Register 1
#define PHID1_ID_Pos    (0U)
#define PHID1_ID_Msk    (0xFFFF << PHID1_ID_Pos)

#define PHID2          0x03    // PHY Identifier Register 2
#define PHID2_ID_Pos     (10U)
#define PHID2_ID_Msk     (0x3F << PHID2_ID_Pos)
#define PHID2_PN_Pos     (4U)
#define PHID2_PN_Msk     (0x3F << PHID2_PN_Pos)
#define PHID2_Rev_Pos    (0U)
#define PHID2_Rev_Msk    (0x0F << PHID2_Rev_Pos)

#define PHCON2         0x10    // PHY Control Register 2
#define PHCON2_FRCLNK_Pos    (14U)    // Force Link
#define PHCON2_FRCLNK_Msk    (0x01 << PHCON2_FRCLNK_Pos)
#define PHCON2_TXDIS_Pos     (13U)    // Transmit Disable
#define PHCON2_TXDIS_Msk     (0x01 << PHCON2_TXDIS_Pos)
#define PHCON2_JABBER_Pos    (10U)    // Jabber Disable
#define PHCON2_JABBER_Msk    (0x01 << PHCON2_JABBER_Pos)
#define PHCON2_HDLDIS_Pos    (8U)     // HDX Disable
#define PHCON2_HDLDIS_Msk    (0x01 << PHCON2_HDLDIS_Pos)

#define PHSTAT2              0x11    // PHY Status Register 2
#define PHSTAT2_PLRITY_Pos   (5U)   // Polarity Status
#define PHSTAT2_PLRITY_Msk   (0x01 << PHSTAT2_PLRITY_Pos)   // Polarity Status mask
#define PHSTAT2_DPXSTAT_Pos  (9U)   // Duplex Status
#define PHSTAT2_DPXSTAT_Msk  (0x01 << PHSTAT2_DPXSTAT_Pos)  // Duplex Status mask
#define PHSTAT2_LSTAT_Pos    (10U)   // Link Status
#define PHSTAT2_LSTAT_Msk    (0x01 << PHSTAT2_LSTAT_Pos)    // Link Status mask
#define PHSTAT2_COLSTAT_Pos  (11U)   // Collision Status
#define PHSTAT2_COLSTAT_Msk  (0x01 << PHSTAT2_COLSTAT_Pos)  // Collision Status mask
#define PHSTAT2_RXSTAT_Pos   (12U)   // Receive Status
#define PHSTAT2_RXSTAT_Msk   (0x01 << PHSTAT2_RXSTAT_Pos)   // Receive Status mask
#define PHSTAT2_TXSTAT_Pos   (13U)   // Transmit Status
#define PHSTAT2_TXSTAT_Msk   (0x01 << PHSTAT2_TXSTAT_Pos)   // Transmit Status mask

#define PHIE               0x12    // PHY Interrupt Enable Register
#define PHIE_PLNKIE_Pos    (4U)     // PHY Link Change Interrupt Enable
#define PHIE_PLNKIE_Msk    (0x01 << PHIE_PLNKIE_Pos)
#define PHIE_PGEIE_Pos     (1U)     // PHY General Interrupt Enable
#define PHIE_PGEIE_Msk     (0x01 << PHIE_PGEIE_Pos)

#define PHIR               0x13    // PHY Interrupt Request Register
#define PHIR_PLNKIF_Pos    (4U)     // PHY Link Change Interrupt Flag
#define PHIR_PLNKIF_Msk    (0x01 << PHIR_PLNKIF_Pos)
#define PHIR_PGIF_Pos      (2U)     // PHY General Interrupt Flag
#define PHIR_PGIF_Msk      (0x01 << PHIR_PGIF_Pos)

#define PHLCON              0x14
#define PHLCON_LACFG3_Pos   (11U)    // LED A Configuration Bit 3
#define PHLCON_LACFG3_Msk   (0x01 << PHLCON_LACFG3_Pos)
#define PHLCON_LACFG2_Pos   (10U)    // LED A Configuration Bit 2
#define PHLCON_LACFG2_Msk   (0x01 << PHLCON_LACFG2_Pos)
#define PHLCON_LACFG1_Pos   (9U)     // LED A Configuration Bit 1
#define PHLCON_LACFG1_Msk   (0x01 << PHLCON_LACFG1_Pos)
#define PHLCON_LACFG0_Pos   (8U)     // LED A Configuration Bit 0
#define PHLCON_LACFG0_Msk   (0x01 << PHLCON_LACFG0_Pos)
#define PHLCON_LBCFG3_Pos   (7U)     // LED B Configuration Bit 3
#define PHLCON_LBCFG3_Msk   (0x01 << PHLCON_LBCFG3_Pos)
#define PHLCON_LBCFG2_Pos   (6U)     // LED B Configuration Bit 2
#define PHLCON_LBCFG2_Msk   (0x01 << PHLCON_LBCFG2_Pos)
#define PHLCON_LBCFG1_Pos   (5U)     // LED B Configuration Bit 1
#define PHLCON_LBCFG1_Msk   (0x01 << PHLCON_LBCFG1_Pos)
#define PHLCON_LBCFG0_Pos   (4U)     // LED B Configuration Bit 0
#define PHLCON_LBCFG0_Msk   (0x01 << PHLCON_LBCFG0_Pos)
#define PHLCON_LFRQ1_Pos    (3U)     // LED Frequency Bit 1
#define PHLCON_LFRQ1_Msk    (0x01 << PHLCON_LFRQ1_Pos)
#define PHLCON_LFRQ0_Pos    (2U)     // LED Frequency Bit 0
#define PHLCON_LFRQ0_Msk    (0x01 << PHLCON_LFRQ0_Pos)
#define PHLCON_STRCH_Pos    (1U)     // LED Strapping Channel
#define PHLCON_STRCH_Msk    (0x01 << PHLCON_STRCH_Pos)

