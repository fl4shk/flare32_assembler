#include "code_generator_class.hpp"


namespace flare32
{

// Code generator stuff
void CodeGenerator::__encode_opcode(u16& high_hword, PInstr instr) const
{
	//for (const auto& outer_iter : __instr_tbl.instr_vec)
	for (size_t j=0; j<__instr_tbl->instr_vec.size(); ++j)
	{
		const auto& outer_iter = __instr_tbl->instr_vec.at(j);

		//for (const auto& other_instr : *outer_iter)
		for (size_t i=0; i<outer_iter->size(); ++i)
		{
			const auto& other_instr = outer_iter->at(i);
			if (instr == other_instr)
			{
				clear_and_set_bits_with_range(high_hword, i, 12, 8);
				return;
			}
		}
	}
}


void CodeGenerator::__encode_high_hword(u16& high_hword, 
	const std::vector<std::string>& regs, s64 expr_result, PInstr instr)
{
	__encode_instr_group(high_hword, instr);
	__encode_affects_flags(high_hword, instr);
	__encode_opcode(high_hword, instr);

	switch (instr->args())
	{
		case InstrArgs::LdStBlock1To4:
		case InstrArgs::LdStBlock5To8:
			// Encode rA
			if (regs.size() >= 2)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(1)).value(), 7, 4);
			}

			// Encode rB
			if (regs.size() >= 3)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(2)).value(), 3, 0);
			}
			
			break;

		default:
			// Encode rA
			if (regs.size() >= 1)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(0)).value(), 7, 4);
			}

			// Encode rB
			if (regs.size() >= 2)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(1)).value(), 3, 0);
			}
			break;
	}

}


void CodeGenerator::__encode_low(u16& g1g2_low, u32& g3_low, 
	const std::vector<std::string>& regs, s64 expr_result, PInstr instr)
{
	auto handle_enc_group_2 = [&]() -> void
	{
		// Non-block moves version
		if (instr->args() != InstrArgs::LdStBlock1To4)
		{
			if (regs.size() == 3)
			{
				clear_and_set_bits_with_range(g1g2_low, 
					builtin_sym_tbl().at(regs.at(2)).value(), 15, 12);
			}
			else if (regs.size() > 3)
			{
				we().err("__encode_low()::handle_enc_group_2() non else:  ",
					"Eek!\n");
			}
			clear_and_set_bits_with_range(g1g2_low, expr_result, 11, 0);
		}

		// Block moves version
		else
		{
			clear_and_set_bits_with_range(g1g2_low, regs.size() - 2, 1, 0);

			clear_and_set_bits_with_range(g1g2_low, 
				builtin_sym_tbl().at(regs.at(0)).value(), 7, 4);

			//if (regs.size() >= 3)
			//{
			//		
			//		
			//}
			if (regs.size() >= 4)
			{
				clear_and_set_bits_with_range(g1g2_low, 
					builtin_sym_tbl().at(regs.at(3)).value(), 15, 12);
			}
			if (regs.size() >= 5)
			{
				clear_and_set_bits_with_range(g1g2_low,
					builtin_sym_tbl().at(regs.at(4)).value(), 11, 8);
			}

			if ((regs.size() < 2) || (regs.size() > 5))
			{
				we().err("__encode_low()::handle_enc_group_2() else:  ",
					"Eek!\n");
			}
		}
	};

	auto handle_enc_group_3 = [&]() -> void
	{
		if ((instr->args() != InstrArgs::LdStBlock5To8)
			&& (instr->args() != InstrArgs::LongMul)
			&& (instr->args() != InstrArgs::LongDivMod)
			&& (instr->args() != InstrArgs::DivMod)
			&& (instr->args() != InstrArgs::LongBitShift))
		{
			//if (regs.size() == 3)
			//{
			//	clear_and_set_bits_with_range(g3_low, 
			//		builtin_sym_tbl().at(regs.at(2)).value(), 15, 12);
			//}
			//else if (regs.size() > 3)
			//{
			//	we().err("__encode_low()::handle_enc_group_3() non else:  ",
			//		"Eek!\n");
			//}
			g3_low = expr_result;
		}

		else if (instr->args() == InstrArgs::LdStBlock5To8)
		{
			clear_and_set_bits_with_range(g3_low, regs.size() - 6, 1, 0);

			clear_and_set_bits_with_range(g3_low, 
				builtin_sym_tbl().at(regs.at(0)).value(), 7, 4);

			//if (regs.size() >= 3)
			//{
			//		
			//		
			//}

			//if (regs.size() >= 4)
			{
				clear_and_set_bits_with_range(g3_low, 
					builtin_sym_tbl().at(regs.at(3)).value(), 31, 28);
			}
			//if (regs.size() >= 5)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(4)).value(), 27, 24);
			}
			if (regs.size() >= 6)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(5)).value(), 23, 20);
			}
			if (regs.size() >= 7)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(6)).value(), 19, 16);
			}
			if (regs.size() >= 8)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(7)).value(), 15, 12);
			}
			if (regs.size() >= 9)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(8)).value(), 11, 8);
			}

			//clear_and_set_bits_with_range(g3_low,
			//	builtin_sym_tbl().at(regs.at()));

			if ((regs.size() < 6) || (regs.size() > 9))
			{
				we().err("__encode_low()::handle_enc_group_3() else:  ",
					"Eek!\n");
			}
		}
		else 
		{
			if (regs.size() >= 3)
			{
				clear_and_set_bits_with_range(g3_low, 
					builtin_sym_tbl().at(regs.at(2)).value(), 31, 28);
			}
			if (regs.size() >= 4)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(3)).value(), 27, 24);
			}
			if (regs.size() >= 5)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(4)).value(), 23, 20);
			}
			if (regs.size() >= 6)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(5)).value(), 19, 16);
			}
			if (regs.size() >= 7)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(6)).value(), 15, 12);
			}
			if (regs.size() >= 8)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(7)).value(), 11, 8);
			}
		}

	};

	switch (instr->enc_group())
	{
		case 0:
			break;

		case 1:
			g1g2_low = expr_result;
			break;

		case 2:
			handle_enc_group_2();
			break;

		case 3:
			handle_enc_group_3();
			break;
	}
}

void CodeGenerator::encode_and_gen
	(const std::vector<std::string>& regs, s64 expr_result, 
	PInstr instr)
{
	u16 high_hword = 0;
	u16 g1g2_low = 0;
	u32 g3_low = 0;

	__encode_high_hword(high_hword, regs, expr_result, instr);
	__encode_low(g1g2_low, g3_low, regs, expr_result, instr);
	gen16(high_hword);
	__gen_low(g1g2_low, g3_low, instr);

	if (can_output())
	{
		printout("\n");
	}

}

void CodeGenerator::__gen_low(u16 g1g2_low, u32 g3_low, PInstr instr) 
{
	switch (instr->enc_group())
	{
		case 0:
			break;

		case 1:
			gen16(g1g2_low);
			break;

		case 2:
			gen16(g1g2_low);
			break;

		case 3:
			gen32(g3_low);
			break;
	}
}


void CodeGenerator::gen8(s32 v)
{
	if (can_output())
	{
		if (last_addr() != addr())
		{
			printf("@%08x\n", static_cast<u32>(addr()));
		}
		printf("%02x\n", (static_cast<u32>(v) & 0xff));
	}

	set_last_addr(set_addr(addr() + 1));
}
void CodeGenerator::gen16(s32 v)
{
	gen8(v >> 8);
	gen8(v);
}
void CodeGenerator::gen32(s32 v)
{
	gen8(v >> 24);
	gen8(v >> 16);
	gen8(v >> 8);
	gen8(v);
}


}
