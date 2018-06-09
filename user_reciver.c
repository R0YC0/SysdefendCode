#include <sys/socket.h>
#include <linux/netlink.h>



int main()
{
	struct msghdr msg;
	struct iovev iov;
	struct sockaddr_nl dest_addr;
	//nlmsghdr -> Message header
	//allocate buffer for netlink message which is message header + message payload
    	struct nlmsghdr *nlh =(struct nlmsghdr *) malloc(NLMSG_SPACE(NLINK_MSG_LEN));
	
	//create socket
	//PF_NETLINK -> protocol family used for communication
	//SOCK_RAW -> the way in which communication is done
	//NETLINK_GENERIC -> protocol specifies which Netlink feature is to be used. 
	int fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_GENERIC);   



	//define netlink client. for example -> unicast o multicast.
	struct sockaddr_nl src_addr;
	

	//This is the identification or the local address of the process. send a unicast message to other processes. 
	//it's 2 and 1 beacuse it's reciver and not sender.
	src_addr.nl_pid = 2;
	
	 
	//AF_NETLINK socket protocol
	src_addr.nl_family = AF_NETLINK;
 
	//specify not a multicast communication
	src_addr.nl_groups = 0;
 
	//attach socket to unique id or address
	bind(fd, (struct sockaddr *)&src_addr, sizeof(src_addr));
	
	


	//NLMSG_SPACE -> Return the number of bytes that a netlink message with payload of len would occupy. netlink macro.
	memset(nlh, 0, NLMSG_SPACE(NLINK_MSG_PAYLOAD));

	
	
	//netlink message header base address
    	iov.iov_base = (void *)nlh;

    	//netlink message length
    	iov.iov_len = nlh->nlmsg_len;
	

	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0; /* For Linux Kernel */
	dest_addr.nl_groups = 0; /* unicast */


	msg.msg_name = (void *)&dest_addr;

    	msg.msg_namelen = sizeof(dest_addr);

    	msg.msg_iov = &iov;

    	msg.msg_iovlen = 1;

    	//receive the message
    	recvmsg(fd, &msg, 0);

    	printf("received message %s\n", NLMSG_DATA(nlh));

	close(fd);
	return 0;
}
