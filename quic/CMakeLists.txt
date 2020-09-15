AUX_SOURCE_DIRECTORY(.                          QUIC_SRCS)
AUX_SOURCE_DIRECTORY(./core                     CORE_SRCS)
AUX_SOURCE_DIRECTORY(./masque                   MASQUE_SRCS)
AUX_SOURCE_DIRECTORY(./platform                 FPLATFORM_SRCS)
AUX_SOURCE_DIRECTORY(./qbone                    QBONE_SRCS)
AUX_SOURCE_DIRECTORY(./quic_transport           QUIC_TRANSPORT_SRCS)

set(ALL_QUIC_SRCS 
    ${QUIC_SRCS}
    ${CORE_SRCS}
    ${MASQUE_SRCS}
    ${FPLATFORM_SRCS}
    ${QBONE_SRCS}
    ${QUIC_TRANSPORT_SRCS}
)

add_library(hippo  STATIC ALL_QUIC_SRCS)