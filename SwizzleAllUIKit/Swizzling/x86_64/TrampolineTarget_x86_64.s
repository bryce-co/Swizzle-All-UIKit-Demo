//
//  TrampolineTarget_x86_64.s
//  SwizzleAllUIKit
//
//  Created by Bryce Pauken on 4/12/20.
//  Copyright © 2020 bryce.co. All rights reserved.
//

#if __x86_64__

.globl  _trampoline_target

// An intermediate function for our individual
// trampolines to call
.p2align 4
_trampoline_target:

// Save argument registers
sub     $0x80, %rsp
movupd  %xmm0, 0x00(%rsp)
movupd  %xmm1, 0x10(%rsp)
movupd  %xmm2, 0x20(%rsp)
movupd  %xmm3, 0x30(%rsp)
movupd  %xmm4, 0x40(%rsp)
movupd  %xmm5, 0x50(%rsp)
movupd  %xmm6, 0x60(%rsp)
movupd  %xmm7, 0x70(%rsp)
pushq   %rdi
pushq   %rax
pushq   %rdx
pushq   %rsi
pushq   %rcx
pushq   %r8
pushq   %r9

// The address that this function will return
// to once finished is placed at the top of
// the stack before the function is called.
// Copy this address (which is now 184 bytes from
// the top of the stack, after our pushes above)
// into `rdi` to act as our first argument
movq    0xB8(%rsp), %rdi

// Call swizzle handler
// (plus setup & teardown the stackframe)
pushq    %rbp
movq     %rsp, %rbp
call    _common_swizzle_handler
popq    %rbp

// Replace our return value with the
// one returned by our swizzle handler.
movq    %rax, 0xB8(%rsp)

// Restore artument registers
popq    %r9
popq    %r8
popq    %rcx
popq    %rsi
popq    %rdx
popq    %rax
popq    %rdi
movupd  0x70(%rsp), %xmm7
movupd  0x60(%rsp), %xmm6
movupd  0x50(%rsp), %xmm5
movupd  0x40(%rsp), %xmm4
movupd  0x30(%rsp), %xmm3
movupd  0x20(%rsp), %xmm2
movupd  0x10(%rsp), %xmm1
movupd  0x00(%rsp), %xmm0
add     $0x80, %rsp

// Return!
ret

#endif
