/*
 * jls_log.h
 *
 *  Created on: Oct 20, 2012
 *      Author: Shengjia Zhu
 */

#ifndef JLS_LOG_H_
#define JLS_LOG_H_

#define LOG_BEGIN_FLAG1			0x01
#define LOG_BEGIN_FLAG2			0x02
#define LOG_END_FLAG			0x03
#define LOG_DEBUG_PREFIX		0x04
#define LOG_INFO_PREFIX			0x0c
#define LOG_WARNING_PREFIX		0x07
#define LOG_ERROR_PREFIX		0x06

#define LOG_INPUT_PREFIX		0x05

/* protocol */
/*
General Log:    | LOG_BEGIN_FLAG1 | LOG_BEGIN_FLAG2 | ***User's Log String*** | LOG_END_FLAG |

Debug Log:      | LOG_BEGIN_FLAG1 | LOG_BEGIN_FLAG2 | LOG_DEBUG_PREFIX | ***User's Log String*** | LOG_END_FLAG |

Info Log:       | LOG_BEGIN_FLAG1 | LOG_BEGIN_FLAG2 | LOG_INFO_PREFIX | ***User's Log String*** | LOG_END_FLAG |

Warning Log:    | LOG_BEGIN_FLAG1 | LOG_BEGIN_FLAG2 | LOG_WARNING_PREFIX | ***User's Log String*** | LOG_END_FLAG |

Error Log:      | LOG_BEGIN_FLAG1 | LOG_BEGIN_FLAG2 | LOG_ERROR_PREFIX | ***User's Log String*** | LOG_END_FLAG |

Request input:  | LOG_BEGIN_FLAG1 | LOG_BEGIN_FLAG2 | LOG_INPUT_PREFIX |

*/

#endif /* JLS_LOG_H_ */
