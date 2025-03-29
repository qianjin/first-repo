typedef struct __UART_RRD{
    UART_INTERFACE_RRD *interface;

    IfxAsclin_Asc asc;

    DMA_DRIVER_RRD tx_dma_driver;
    IfxDma_ChannelId tx_channel_id;
    size_t remaining_bytes_to_dma;

    DMA_DRIVER_RRD rx_dma_driver;
    IfxDma_ChannelId rx_channel_id;
    DMA_CIRCULAR_QUEUE_RRD rx_buff;

}UART_RRD;

// 更新队列消息
static void uart_rx_dma_update_buff_info_rrd(UART_RRD *self)
{
    size_t count = IfxDma_getChannelDestinationAddress(self->rx_dma_driver.dma_chn.dma,
                                                        self->rx_dma_driver.dma_chn.channelId) - (size_t)self->rx_buff.data;
    self->rx_buff.rear = count;

    if(self->rx_buff.dma_wrap_count && self->rx_buff.rear > self->rx_buff.front){
        self->rx_buff.is_full = true;
        self->rx_buff.dma_wrap_count = 0;
        self->rx_buff.front = self->rx_buff.rear;
    }
}

// 放在中断函数内 每次dma队列回绕时记录回绕次数
static inline void uart_rx_dma_iqr_handle_rrd(UART_RRD *uart)
{
    # if debug_disable
    printf("p: %p s: %p \r\n",IfxDma_getChannelDestinationAddress(uart->rx_dma_driver.dma_chn.dma,uart->rx_dma_driver.dma_chn.channelId),uart->rx_buff.data);
    #endif
    if(IfxDma_getAndClearChannelWrapDestinationBufferInterrupt(uart->rx_dma_driver.dma_chn.dma,
                                                                uart->rx_dma_driver.dma_chn.channelId)){
        ++uart->rx_buff.dma_wrap_count;
    }
}

// 每次解析数据
static inline void host_prase_messgae_app(void){
    g_USART_0.interface->rx_dma_update_buff_info(&g_USART_0); // 更新队列消息
    size_t length = g_USART_0.rx_buff.interface->get_lenth(&g_USART_0.rx_buff); // 获取数据长度
    if(length > g_HOST_START_PARASE_SIZE){
        uint8_t *data;
        bool ret = false;
        DMA_CIRCULAR_QUEUE_RRD *buff = &g_USART_0.rx_buff;
        dma_circular_queue_for_each(buff,data){ // 遍历字节数据(取出每一位数据)
            ret = g_HOST_PROTOCOL->interface->parse_packet(g_HOST_PROTOCOL,data,0,0);
            if(ret){
                break;
            }
        }
    }
}
