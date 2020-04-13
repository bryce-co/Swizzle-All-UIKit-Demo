# Swizzle All Of UIKit

Example project for swizzling every UIKitCore method, based on
[this post](https://bryce.co/swizzle-all-uikit/) on [bryce.co](https://bryce.co/).

### Notes:

- This project currently supports `x86_64` (e.g., the iOS Simulator, not an actual device) only.
  I do plan on adding an `arm64` implementation in the future.
- As mentioned at the end of the accompanying blog post, this implementation
  can scale up even further (and be made more space-efficient) using `vm_remap`.
