/*----------------------------------------------------------------------------
 * Tencent is pleased to support the open source community by making TencentOS
 * available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
 * If you have downloaded a copy of the TencentOS binary from Tencent, please
 * note that the TencentOS binary is licensed under the BSD 3-Clause License.
 *
 * If you have downloaded a copy of the TencentOS source code from Tencent,
 * please note that TencentOS source code is licensed under the BSD 3-Clause
 * License, except for the third-party components listed below which are
 * subject to different license terms. Your integration of TencentOS into your
 * own projects may require compliance with the BSD 3-Clause License, as well
 * as the other licenses applicable to the third-party components included
 * within TencentOS.
 *---------------------------------------------------------------------------*/

#ifndef _TOS_QUEUE_H_
#define  _TOS_QUEUE_H_

#if TOS_CFG_QUEUE_EN > 0u

typedef struct k_queue_st {
    pend_obj_t      pend_obj;
    k_msg_queue_t   msg_queue;
} k_queue_t;

/**
 * @brief Create a queue.
 * create a queue.
 *
 * @attention None
 *
 * @param[in]   queue       pointer to the handler of the queue.
 *
 * @return  errcode
 * @retval  #K_ERR_NONE                   return successfully.
 */
__API__ k_err_t tos_queue_create(k_queue_t *queue);

/**
 * @brief Destroy a queue.
 * destroy a queue.
 *
 * @attention None
 *
 * @param[in]   queue       pointer to the handler of the queue.
 *
 * @return  errcode
 * @retval  #K_ERR_NONE                   return successfully.
 */
__API__ k_err_t tos_queue_destroy(k_queue_t *queue);

/**
 * @brief Pend a queue.
 * pend a queue.
 *
 * @attention we DONNOT perform a memcpy when msg_addr returned, we just let the *msg_addr point to an inner memory block.
 *            that means you DONNOT need to alloc memory for msg_addr, msg_addr can just be a pointer.
 *
 * @param[in]   queue       pointer to the handler of the queue.
 * @param[out]  msg_addr    a pointer point to the message we wanna recive.
 * @param[out]  msg_size    pointer to the message size returned.
 * @param[in]   timeout     how much time(in k_tick_t) we would like to wait.
 *
 * @return  errcode
 * @retval  #K_ERR_PEND_NOWAIT                we get nothing, and we don't wanna wait.
 * @retval  #K_ERR_PEND_SCHED_LOCKED          we can wait, but scheduler is locked.
 * @retval  #K_ERR_PEND_TIMEOUT               the time we wait is up, we get nothing.
 * @retval  #K_ERR_PEND_DESTROY               the queue we are pending is destroyed.
 * @retval  #K_ERR_NONE                       return successfully.
 */
__API__ k_err_t tos_queue_pend(k_queue_t *queue, void **msg_addr, size_t *msg_size, k_tick_t timeout);

/**
 * @brief Post a queue.
 * post a queue and wakeup one pending task.
 *
 * @attention when tos_queue_post return successfully, only one task who are waitting for the queue will be woken up.
 *
 * @param[in]   queue       pointer to the handler of the queue.
 *
 * @return  errcode
 * @retval  #K_ERR_QUEUE_FULL                 the message pool is full.
 * @retval  #K_ERR_NONE                       return successfully.
 */
__API__ k_err_t tos_queue_post(k_queue_t *queue, void *msg_addr, size_t msg_size);

/**
 * @brief Post a queue.
 * post a queue and wakeup all the pending task.
 *
 * @attention when tos_queue_post_all return successfully, all of the tasks who are waitting for the queue will be woken up.
 *
 * @param[in]   queue       pointer to the handler of the queue.
 *
 * @return  errcode
 * @retval  #K_ERR_QUEUE_FULL                 the message pool is full.
 * @retval  #K_ERR_NONE                       return successfully.
 */
__API__ k_err_t tos_queue_post_all(k_queue_t *queue, void *msg_addr, size_t msg_size);

/**
 * @brief Flush a queue.
 * flush a queue, clear all the msg in the queue.
 *
 * @attention None
 *
 * @param[in]   queue       pointer to the handler of the queue.
 *
 * @return  errcode
 * @retval  #K_ERR_NONE                   return successfully.
 */
__API__ k_err_t tos_queue_flush(k_queue_t *queue);

/**
 * @brief Remove one message from the queue.
 * Remove one message with certain address from the queue.
 *
 * @attention None
 *
 * @param[in]   queue       pointer to the handler of the queue.
 * @param[in]   msg_addr    the address of the message.
 *
 * @return  errcode
 * @retval  #K_ERR_QUEUE_MSG_NOT_EXIST      message to remove is not existed.
 * @retval  #K_ERR_NONE                     return successfully.
 */
__API__ k_err_t tos_queue_remove(k_queue_t *queue, void *msg_addr);

#endif

#endif /* _TOS_QUEUE_H_ */

