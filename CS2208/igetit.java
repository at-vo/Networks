public class igetit {

	public static void main(String args[]) {

		String num = "013800150738";

		int sum1 = 0;
		int sum2 = 0;

		for (int i = 0; i < num.length(); i++) {
			int at = num.charAt(i) - 48;

			if (i % 2 == 0) {
				sum1 += at;
			} else {
				sum2 += at;
			}
		}

		sum1 *= 3;
		sum2 += sum1;
		if (sum2 % 10 == 0) {
			System.out.println("ok");
		} else {
			System.out.println("not ok");
		}
	}
}