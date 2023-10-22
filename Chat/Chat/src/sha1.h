#ifndef IPVSDK_SECURITY_SHA1_HEADER_
#define IPVSDK_SECURITY_SHA1_HEADER_

typedef unsigned int Uint32;

namespace ipvsdk {
namespace security {
class SHA1
{
	private:
		// fields
		Uint32 H0, H1, H2, H3, H4;
		unsigned char bytes[64];
		int unprocessedBytes;
		Uint32 size;
		void process();
	public:
		SHA1();
		~SHA1();
		void addBytes( const char* data, int num );
		unsigned char* getDigest();
		// utility methods
		static Uint32 lrot( Uint32 x, int bits );
		static void storeBigEndianUint32( unsigned char* byte, Uint32 num );
		static void hexPrinter( unsigned char* c, int l );
};
}
}
#endif /* IPVSDK_SECURITY_SHA1_HEADER_ */